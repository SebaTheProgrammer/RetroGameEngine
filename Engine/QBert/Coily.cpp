#include "Coily.h"
#include <GameTime.h>
#include <iostream>


Coily::Coily( dae::GameObject* parentGameObject, 
	std::shared_ptr<dae::Texture2D> textureCoily ):
	BaseComponent( parentGameObject )
{																										//Hardcoded values for the animation
	m_pTextureCoily = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureCoily, 1.0f, 2, 8, 0, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
}

void Coily::Update()
{
	m_Timer += dae::GameTime::GetInstance().GetDeltaTime();
	if ( !m_Started ) 
	{
		if ( m_Timer >= m_StartTime )
		{
			m_Timer = 0.f;
			m_Started = true;
			m_CurrentState = AnimationState::Egg;
			m_pSingleMovenment->SetCanMove( true );
		}
	}
	else {
		switch ( m_CurrentState )
		{
		case AnimationState::IdleSnake:
			m_pTextureCoily->SetMinColumns( 0 );
			m_pTextureCoily->SetMaxColumns( 4 );
			m_pTextureCoily->SetMinRows( 0 );
			m_pTextureCoily->SetMaxRows( 1 );
			//jump down, left or right
			break;
		case AnimationState::IdleBackSnake:
			m_pTextureCoily->SetMinColumns( 4 );
			m_pTextureCoily->SetMaxColumns( 8 );
			m_pTextureCoily->SetMinRows( 0 );
			m_pTextureCoily->SetMaxRows( 1 );
			//jump up, left or right
			break;
		case AnimationState::Egg:
			m_pTextureCoily->SetMinColumns( 0 );
			m_pTextureCoily->SetMaxColumns( 4 );
			m_pTextureCoily->SetMinRows( 1 );
			m_pTextureCoily->SetMaxRows( 2 );

			if ( m_Timer >= m_JumpTime )
			{
				m_Timer = 0.f;
				//check if the egg is on the bottom of the pyramid
				//yes, become snake
				//no, stay egg and fall when possible, left or right
				bool random = rand() % 2;
				if ( random==0 )
				{
					Jump( SingleMovementComponent::Direction::LeftDown );
				}
				else
				{
					Jump( SingleMovementComponent::Direction::RightDown );
				}
			}
			break;
		}
	}
	m_pSingleMovenment->Update();
	m_pTextureCoily->Update();
}

void Coily::Render() const
{
	if ( m_Started ) 
	{
		m_pTextureCoily->Render();
	}
}

void Coily::Jump( SingleMovementComponent::Direction dir )
{
	if ( dir == SingleMovementComponent::Direction::LeftUp ) m_pSingleMovenment->SingleMove( glm::vec2{ -0.75f, -1.2f }, dir );
	else if ( dir == SingleMovementComponent::Direction::RightUp ) m_pSingleMovenment->SingleMove( glm::vec2{ 0.75f, -1.2f }, dir );
	else if ( dir == SingleMovementComponent::Direction::RightDown ) m_pSingleMovenment->SingleMove( glm::vec2{ 0.75f, 1.2f }, dir );
	else if ( dir == SingleMovementComponent::Direction::LeftDown ) m_pSingleMovenment->SingleMove( glm::vec2{ -0.75f, 1.2f }, dir );
}

void Coily::SetAnimationState( AnimationState state )
{
	m_CurrentState = state;
}

void Coily::SetPyramidPosition( const int x, const int y )
{
	m_Row = x;
	m_Col = y;
}

void Coily::Moved( SingleMovementComponent::Direction dir )
{
	int oldActiveRow = m_Row;

	if ( m_CurrentState == AnimationState::Egg )
	{
		switch ( dir )
		{
		case SingleMovementComponent::Direction::LeftUp:
			m_Col -= oldActiveRow;
			m_Row -= 1;
			break;
		case SingleMovementComponent::Direction::LeftDown:
			m_Col += oldActiveRow;
			m_Row += 1;
			std::cout<<"LeftDown"<<std::endl;
			break;
		case SingleMovementComponent::Direction::RightDown:
			m_Col += oldActiveRow;
			m_Row += 1;
			std::cout << "RightDown" << std::endl;
			break;
		case SingleMovementComponent::Direction::RightUp:
			m_Col -= oldActiveRow - 1;
			m_Row -= 1;
			break;
		}
	}
	else
	{
		switch ( dir )
		{
		case SingleMovementComponent::Direction::LeftUp:
			SetAnimationState( AnimationState::IdleBackSnake );
			Mirror( true );
			break;
		case SingleMovementComponent::Direction::RightDown:
			SetAnimationState( AnimationState::IdleSnake );
			Mirror( false );
			break;
		case SingleMovementComponent::Direction::LeftDown:
			SetAnimationState( AnimationState::IdleSnake );
			Mirror( true );
			break;
		case SingleMovementComponent::Direction::RightUp:
			SetAnimationState( AnimationState::IdleBackSnake );
			Mirror( false );
			break;
		}
	}

	//int rowStartIndex = ( ( m_Row - 1 ) * m_Row ) / 2;
	//int rowEndIndex = rowStartIndex + m_Row - 1;

	std::cout << "Coily moved to row: " << m_Row << " and col: " << m_Col << std::endl;
}
