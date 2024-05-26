#include "UggWrongWay.h"
#include <GameTime.h>

UggWrongWay::UggWrongWay( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureUggWrongWay, int levelSize, PyramidCubes* pyramid ) :
	BaseComponent( parentGameObject ),
	m_pPyramid( pyramid ),
	m_LevelSize( levelSize )
{
	m_pTextureUggWrongWay = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureUggWrongWay, 2.0f, 2, 4, 0, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_pSingleMovenment->SetCanMove( true );
	m_LevelSize = levelSize;

	m_pTextureUggWrongWay->SetCurrentColumn( 0 );
	m_pTextureUggWrongWay->SetMaxColumns( 1 );
}

void UggWrongWay::Update()
{
	if ( !m_IsAlive ) return;
	if ( !m_CanMove ) return;
	m_Timer += dae::GameTime::GetInstance().GetDeltaTime();

	switch ( m_CurrentState )
	{
	case AnimationState::front:
		if ( m_Timer >= m_JumpTime )
		{
			m_Timer = 0.f;
			Jump();
		}
		break;
	case AnimationState::back:
		if ( m_Timer >= m_JumpTime )
		{
			m_Timer = 0.f;
			Jump();
		}
		break;
	}

	m_pSingleMovenment->Update();
	m_pTextureUggWrongWay->Update();

	if ( m_pPyramid->GetActiveRow() == m_Col and m_pPyramid->GetActiveColumn() == m_Row )
	{
		m_IsAlive = false;
		m_pPyramid->PlayerHit();
	}
}

void UggWrongWay::Render() const
{
	if ( !m_IsAlive ) return;
	m_pTextureUggWrongWay->Render();
}

void UggWrongWay::Jump()
{
	srand( rand() );

	bool random = rand() % 2;
	if ( random == 1 ) m_pSingleMovenment->SingleMove( glm::vec2{ 0.75f, 1.2f }, SingleMovementComponent::Direction::RightUp );
	if ( random == 0 ) m_pSingleMovenment->SingleMove( glm::vec2{ -0.75f, 1.2f }, SingleMovementComponent::Direction::LeftUp );
}

void UggWrongWay::SetAnimationState( AnimationState state )
{
	m_CurrentState = state;
}

void UggWrongWay::SetPyramidPosition( const int x, const int y )
{
	m_Row = x;
	m_Col = y;
}

void UggWrongWay::Moved( SingleMovementComponent::Direction dir )
{
	int oldActiveCol = m_Col;
	switch ( dir )
	{
	case SingleMovementComponent::Direction::LeftUp:
		SetAnimationState( AnimationState::front );
		Mirror( true );
		m_Row += oldActiveCol;
		m_Col += 1;
		break;
	case SingleMovementComponent::Direction::RightUp:
		SetAnimationState( AnimationState::front );
		Mirror( false );
		m_Row += oldActiveCol + 1;
		m_Col += 1;
		break;
	}

	if ( m_Col > m_LevelSize )
	{
		m_IsAlive = false;
		return;
	}
}

int UggWrongWay::GetRowStartIndex( int col ) const
{
	return ( ( col - 1 ) * ( col ) ) / 2;
}

int UggWrongWay::GetRowEndIndex( int col ) const
{
	return  GetRowStartIndex( col ) + col - 1;
}