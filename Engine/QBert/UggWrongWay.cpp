#include "UggWrongWay.h"
#include <GameTime.h>
#include <iostream>
#include "Utilities.h"
#include "MovementManager.h"

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

	m_IsGoingUp = rand() % 2;
}

void UggWrongWay::Update()
{
	if ( !m_IsAlive ) return;
	if ( !m_CanMove ) return;
	SetStartPos();

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

	if ( m_pPyramid->GetActiveRow() == m_Col and m_pPyramid->GetActiveColumn() == m_Row && m_IsAlive ==true)
	{
		m_IsAlive = false;
		m_pPyramid->Player1Hit();
	}

	else if ( m_pPyramid->GetActiveRow2() == m_Col and m_pPyramid->GetActiveColumn2() == m_Row && m_IsAlive == true )
	{
		m_IsAlive = false;
		m_pPyramid->Player2Hit();
	}
}

void UggWrongWay::Render() const
{
	if ( !m_IsAlive ) return;
	m_pTextureUggWrongWay->Render();
}

void UggWrongWay::Jump()
{
	auto movement = MovementManager::GetInstance();

	if ( m_IsGoingUp ) 
	{
		if ( m_IsInLeftCorner ) m_pSingleMovenment->SingleMove( movement.Rightup.vector, movement.Rightup.direction, true );
		if ( !m_IsInLeftCorner ) m_pSingleMovenment->SingleMove( movement.Leftup.vector, movement.Leftup.direction, true );
	}
	else
	{
		if ( m_Up )
		{
			if ( m_IsInLeftCorner )
			{
				m_pSingleMovenment->SingleMove( movement.Rightup.vector, movement.Rightup.direction, true );
			}
			else
			{
				m_pSingleMovenment->SingleMove( movement.Leftup.vector, movement.Leftup.direction, true );
			}

			m_Up = false;
		}
		else
		{
			if ( m_IsInLeftCorner )
			{
				m_pSingleMovenment->SingleMove( movement.Rightdown.vector, movement.Rightdown.direction, true );
			}
			else
			{
				m_pSingleMovenment->SingleMove( movement.Leftdown.vector, movement.Leftdown.direction, true );
			}

			m_Up = true;
		}
	}
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
		m_Row -= oldActiveCol;
		m_Col -= 1;
		break;
	case SingleMovementComponent::Direction::RightDown:
		m_Row += oldActiveCol + 1;
		m_Col += 1;
		break;
	case SingleMovementComponent::Direction::LeftDown:
		m_Row += oldActiveCol;
		m_Col += 1;
		break;
	case SingleMovementComponent::Direction::RightUp:
		SetAnimationState( AnimationState::front );
		m_Row -= oldActiveCol - 1;
		m_Col -= 1;
		break;
	}

	if ( m_Col <= 1 || m_Row > GetRowEndIndex( m_Col ) || m_Row < GetRowStartIndex( m_Col ) )
	{
		m_IsAlive = false;
		return;
	}
}

void UggWrongWay::SetStartPos()
{
	if ( m_SettetStartPos ) return;

	srand( rand() );

	bool random = rand() % 2;

	auto movement = MovementManager::GetInstance();

	for ( int i = 0; i < m_LevelSize; ++i )
	{
		if ( random == 1 )
		{
			m_IsInLeftCorner = true;
			m_pSingleMovenment->SingleMove( movement.Leftdown.vector, movement.Leftdown.direction, true );
		}
		else 
		{
			m_pSingleMovenment->SingleMove( movement.Rightdown.vector, movement.Rightdown.direction, true );
			Mirror( true );
		}
	}
	m_SettetStartPos= true;
}
