#include "Coily.h"
#include <GameTime.h>
#include <iostream>


Coily::Coily( dae::GameObject* parentGameObject, 
	std::shared_ptr<dae::Texture2D> textureCoily, int levelSize ):
	BaseComponent( parentGameObject )
{																										//Hardcoded values for the animation
	m_pTextureCoily = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureCoily, 1.0f, 2, 8, 0, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_LevelSize = levelSize;
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
			//Animations
			m_pTextureCoily->SetMinColumns( 0 );
			m_pTextureCoily->SetMaxColumns( 4 );
			m_pTextureCoily->SetMinRows( 0 );
			m_pTextureCoily->SetMaxRows( 1 );
			if ( m_Timer >= m_JumpTime )
			{
				m_Timer = 0.f;
				FollowPlayer( 0, 0 );
			}
			break;
		case AnimationState::IdleBackSnake:
			//Animations
			m_pTextureCoily->SetMinColumns( 4 );
			m_pTextureCoily->SetMaxColumns( 8 );
			m_pTextureCoily->SetMinRows( 0 );
			m_pTextureCoily->SetMaxRows( 1 );
			if ( m_Timer >= m_JumpTime )
			{
				m_Timer = 0.f;
				FollowPlayer( 0, 0 );
			}
			break;
		case AnimationState::Egg:
			//Animations
			m_pTextureCoily->SetMinColumns( 0 );
			m_pTextureCoily->SetMaxColumns( 4 );
			m_pTextureCoily->SetMinRows( 1 );
			m_pTextureCoily->SetMaxRows( 2 );

			if ( m_Timer >= m_JumpTime )
			{
				m_Timer = 0.f;
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
	int oldActiveCol = m_Col;
	if ( m_CurrentState == AnimationState::Egg )
	{
		switch ( dir )
		{
		case SingleMovementComponent::Direction::LeftDown:
			m_Row += oldActiveCol;
			m_Col += 1;
			break;
		case SingleMovementComponent::Direction::RightDown:
			m_Row += oldActiveCol + 1;
			m_Col += 1;
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

	int rowStartIndex = GetRowStartIndex(m_Col);
	int rowEndIndex = GetRowEndIndex(m_Col);

	if ( ( m_Row < 0 || m_Col >= m_LevelSize ) || ( m_Row < rowStartIndex || m_Row > rowEndIndex ) || m_Col == 0 )
	{
		//At the bottom of the pyramid
		SetAnimationState( AnimationState::IdleSnake );
		return;
	}
}

void Coily::FollowPlayer( int playerRow, int playerCol )
{
	if ( m_Row != playerRow || m_Col != playerCol )
	{
		int oldActiveCol = m_Col;

		// Calculate the potential new positions
		int newRow{}, newCol{};
		SingleMovementComponent::Direction direction{};

		if ( playerRow < m_Row && playerCol < m_Col )
		{
			newRow = m_Row - oldActiveCol;
			newCol = m_Col - 1;
			direction = SingleMovementComponent::Direction::LeftUp;
		}
		if ( playerRow > m_Row && playerCol > m_Col )
		{
			newRow = m_Row + oldActiveCol + 1;
			newCol = m_Col + 1;
			direction = SingleMovementComponent::Direction::RightDown;
		}
		if ( playerRow > m_Row && playerCol < m_Col )
		{
			newRow = m_Row + oldActiveCol;
			newCol = m_Col + 1;
			direction = SingleMovementComponent::Direction::LeftDown;
		}
		if ( playerRow < m_Row && playerCol > m_Col )
		{
			newRow = m_Row - oldActiveCol - 1;
			newCol = m_Col - 1;
			direction = SingleMovementComponent::Direction::RightUp;
		}

		int rowStartIndex = GetRowStartIndex( newCol );
		int rowEndIndex = GetRowEndIndex( newCol );

		if ( ( newRow >= 0 && newCol < m_LevelSize ) &&
			( newRow >= rowStartIndex && newRow <= rowEndIndex ) &&
			newCol != 0 )
		{
			m_Row = newRow;
			m_Col = newCol;
			Jump( direction );
			m_PrevDirection=direction;
		}
		else
		{
			SingleMovementComponent::Direction invdirection{};
			switch ( m_PrevDirection )
			{
			case SingleMovementComponent::Direction::LeftUp:
				newRow = m_Row + oldActiveCol + 1;
				newCol = m_Col + 1;
				invdirection = SingleMovementComponent::Direction::RightDown;
				break;
			case SingleMovementComponent::Direction::RightDown:
				newRow = m_Row - oldActiveCol;
				newCol = m_Col - 1;
				invdirection = SingleMovementComponent::Direction::LeftUp;
				break;
			case SingleMovementComponent::Direction::LeftDown:
				newRow = m_Row - oldActiveCol - 1;
				newCol = m_Col - 1;
				invdirection = SingleMovementComponent::Direction::RightUp;
				break;
			case SingleMovementComponent::Direction::RightUp:
				newRow = m_Row + oldActiveCol;
				newCol = m_Col + 1;
				invdirection = SingleMovementComponent::Direction::LeftDown;
				break;
			default:
				break;
			}
			Jump( invdirection );
			m_PrevDirection = invdirection;

			m_Row = newRow;
			m_Col = newCol;
		}
	}
}

int Coily::GetRowStartIndex(int col) const
{
	return ( ( col - 1 ) * ( col ) ) / 2;
}

int Coily::GetRowEndIndex( int col ) const
{
	return  GetRowStartIndex( col ) + col - 1;
}
