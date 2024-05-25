#include "Coily.h"
#include <GameTime.h>
#include <iostream>


Coily::Coily( dae::GameObject* parentGameObject, 
	std::shared_ptr<dae::Texture2D> textureCoily, int levelSize, PyramidCubes* pyramid ):
	BaseComponent( parentGameObject ), m_pPyramid( pyramid )
{																										//Hardcoded values for the animation
	m_pTextureCoily = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureCoily, 1.0f, 2, 8, 0, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_pSingleMovenment->SetCanMove( true );
	m_LevelSize = levelSize;
	Egged();
}

void Coily::Update()
{
	if ( !m_CanMove ) return;

	m_Timer += dae::GameTime::GetInstance().GetDeltaTime();

	switch ( m_CurrentState )
	{
	case AnimationState::IdleSnake:
		if ( m_Timer >= m_JumpTime )
		{
			m_Timer = 0.f;
			if ( !m_HasHitPlayer )
			{
				FollowPlayer( m_pPyramid->GetActiveRow(), m_pPyramid->GetActiveColumn() );
			}
		}
		break;
	case AnimationState::IdleBackSnake:
		if ( m_Timer >= m_JumpTime )
		{
			m_Timer = 0.f;
			if ( !m_HasHitPlayer )
			{
				FollowPlayer( m_pPyramid->GetActiveRow(), m_pPyramid->GetActiveColumn() );
			}
		}
		break;
	case AnimationState::Egg:
		if ( m_Timer >= m_JumpTime )
		{
			m_Timer = 0.f;
			srand( rand() );
			bool random = rand() % 2;
			if ( random == 0 )
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

	if ( !m_HasHitPlayer )
	{
		if ( m_pPyramid->GetActiveRow() == m_Col and m_pPyramid->GetActiveColumn() == m_Row )
		{

			m_pPyramid->PlayerHit();
			m_HasHitPlayer = true;
		}
	}
	else 
	{
		m_TimerRespawn += dae::GameTime::GetInstance().GetDeltaTime();

		if ( m_TimerRespawn >= m_RespawnTime )
		{
			m_TimerRespawn = 0.f;
			m_HasHitPlayer = false;
		}
	}

	m_pSingleMovenment->Update();
	m_pTextureCoily->Update();
}

void Coily::Render() const
{
	m_pTextureCoily->Render();
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
			IdleBackSnake();
			Mirror( true );
			break;
		case SingleMovementComponent::Direction::RightDown:
			IdleSnake();
			Mirror( false );
			break;
		case SingleMovementComponent::Direction::LeftDown:
			IdleSnake();
			Mirror( true );
			break;
		case SingleMovementComponent::Direction::RightUp:
			IdleBackSnake();
			Mirror( false );
			break;
		}
	}

	int rowStartIndex = GetRowStartIndex(m_Col);
	int rowEndIndex = GetRowEndIndex(m_Col);

	if ( ( m_Row < 0 || m_Col >= m_LevelSize ) || ( m_Row < rowStartIndex || m_Row > rowEndIndex ) || m_Col == 0 )
	{
		//At the bottom of the pyramid
		//CanTakeControl for multiplayer = true
		IdleSnake();
	}
}

void Coily::FollowPlayer( int playerRow, int playerCol )
{
	int oldActiveCol = m_Col;
	srand( rand() );

	// Calculate the potential new positions
	int newRow{}, newCol{};
	SingleMovementComponent::Direction direction{};

	if ( playerRow <= m_Row ) // Player is above Coily
	{
		if ( playerCol <= m_Col ) // Player is to the left
		{
			// Prefer LeftUp, fallback to RightUp
			newRow = m_Row - oldActiveCol;
			newCol = m_Col - 1;
			direction = SingleMovementComponent::Direction::LeftUp;

			int rowStartIndex = GetRowStartIndex( newCol );
			int rowEndIndex = GetRowEndIndex( newCol );

			if ( newRow < 0 || newRow < rowStartIndex || newRow > rowEndIndex || newCol == 0 )
			{
				newRow = m_Row - oldActiveCol + 1;
				newCol = m_Col - 1;
				direction = SingleMovementComponent::Direction::RightUp;
			}
		}
		else // Player is to the right
		{
			// Prefer RightUp, fallback to LeftUp
			newRow = m_Row - oldActiveCol + 1;
			newCol = m_Col - 1;
			direction = SingleMovementComponent::Direction::RightUp;

			int rowStartIndex = GetRowStartIndex( newCol );
			int rowEndIndex = GetRowEndIndex( newCol );

			if ( newRow < 0 || newRow < rowStartIndex || newRow > rowEndIndex || newCol == 0 )
			{
				newRow = m_Row - oldActiveCol;
				newCol = m_Col - 1;
				direction = SingleMovementComponent::Direction::LeftUp;
			}
		}
	}
	else if ( playerRow > m_Row ) // Player is below Coily
	{
		if ( playerCol <= m_Col ) // Player is to the left
		{
			// Prefer LeftDown, fallback to RightDown
			newRow = m_Row + oldActiveCol;
			newCol = m_Col + 1;
			direction = SingleMovementComponent::Direction::LeftDown;

			int rowStartIndex = GetRowStartIndex( newCol );
			int rowEndIndex = GetRowEndIndex( newCol );

			if ( newRow < 0 || newRow < rowStartIndex || newRow > rowEndIndex || newCol == 0 )
			{
				newRow = m_Row + oldActiveCol + 1;
				newCol = m_Col + 1;
				direction = SingleMovementComponent::Direction::RightDown;
			}
		}
		else // Player is to the right
		{
			// Prefer RightDown, fallback to LeftDown
			newRow = m_Row + oldActiveCol + 1;
			newCol = m_Col + 1;
			direction = SingleMovementComponent::Direction::RightDown;

			int rowStartIndex = GetRowStartIndex( newCol );
			int rowEndIndex = GetRowEndIndex( newCol );

			if ( newRow < 0 || newRow < rowStartIndex || newRow > rowEndIndex || newCol == 0 )
			{
				newRow = m_Row + oldActiveCol;
				newCol = m_Col + 1;
				direction = SingleMovementComponent::Direction::LeftDown;
			}
		}
	}

	int rowStartIndex = GetRowStartIndex( newCol );
	int rowEndIndex = GetRowEndIndex( newCol );

	if ( ( newRow > 0 && newCol < m_LevelSize ) &&
		( newRow >= rowStartIndex && newRow <= rowEndIndex ) &&
		newCol != 0 )
	{
		m_Row = newRow;
		m_Col = newCol;
		Jump( direction );
		m_PrevDirection = direction;
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

void Coily::IdleSnake()
{
	//Animations
	m_pTextureCoily->SetCurrentColumn( 1 );
	m_pTextureCoily->SetMinColumns( 0 );
	m_pTextureCoily->SetMaxColumns( 4 );
	m_pTextureCoily->SetMinRows( 0 );
	m_pTextureCoily->SetMaxRows( 1 );
	SetAnimationState( AnimationState::IdleSnake );
}

void Coily::IdleBackSnake()
{
	//Animations
	m_pTextureCoily->SetCurrentColumn( 5 );
	m_pTextureCoily->SetMinColumns( 4 );
	m_pTextureCoily->SetMaxColumns( 8 );
	m_pTextureCoily->SetMinRows( 0 );
	m_pTextureCoily->SetMaxRows( 1 );
	SetAnimationState( AnimationState::IdleBackSnake );
}

void Coily::Egged()
{
	m_pTextureCoily->SetCurrentColumn( 0 );
	m_pTextureCoily->SetCurrentRow( 1 );
	m_pTextureCoily->SetMinColumns( 0 );
	m_pTextureCoily->SetMaxColumns( 4 );
	m_pTextureCoily->SetMinRows( 1 );
	m_pTextureCoily->SetMaxRows( 2 );
}
