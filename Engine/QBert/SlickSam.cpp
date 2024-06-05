#include "SlickSam.h"
#include <GameTime.h>
#include <iostream>
#include "Utilities.h"

SlickSam::SlickSam( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureUgg, int levelSize, PyramidCubes* pyramid ) :
	BaseComponent( parentGameObject ), m_pPyramid( pyramid )
{
	m_pTextureCoily = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureUgg, 1.0f, 1, 4, 0, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_pSingleMovenment->SetCanMove( true );
	m_LevelSize = levelSize;
}

void SlickSam::Update()
{
	if(!m_IsAlive ) return;
	if(!m_CanMove ) return;

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
	m_pTextureCoily->Update();

	if ( m_pPyramid->GetActiveRow() == m_Col and m_pPyramid->GetActiveColumn() == m_Row && m_IsAlive == true )
	{
		m_IsAlive = false;
		m_pPyramid->KilledEnemy();
	}

	if ( m_pPyramid->GetActiveRow2() == m_Col and m_pPyramid->GetActiveColumn2() == m_Row && m_IsAlive == true )
	{
		m_IsAlive = false;
		m_pPyramid->KilledEnemy();
	}
}

void SlickSam::Render() const
{
	if ( !m_IsAlive ) return;
	m_pTextureCoily->Render();
}

void SlickSam::Jump()
{
	srand( rand() );

	bool random = rand() % 2;
	if ( random == 1 ) m_pSingleMovenment->SingleMove( glm::vec2{ 0.75f, 1.2f }, SingleMovementComponent::Direction::RightDown, true );
	if ( random == 0 ) m_pSingleMovenment->SingleMove( glm::vec2{ -0.75f, 1.2f }, SingleMovementComponent::Direction::LeftDown, true );
}

void SlickSam::SetAnimationState( AnimationState state )
{
	m_CurrentState = state;
}

void SlickSam::SetPyramidPosition( const int x, const int y )
{
	m_Row = x;
	m_Col = y;
}

void SlickSam::Moved( SingleMovementComponent::Direction dir )
{
	int oldActiveCol = m_Col;
	switch ( dir )
	{
	case SingleMovementComponent::Direction::LeftDown:
		SetAnimationState( AnimationState::front );
		Mirror( true );
		m_Row += oldActiveCol;
		m_Col += 1;
		break;
	case SingleMovementComponent::Direction::RightDown:
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

	m_pPyramid->ReverseCube( m_Row );
}
