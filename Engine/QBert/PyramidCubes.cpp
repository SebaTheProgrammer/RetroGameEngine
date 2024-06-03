#include "PyramidCubes.h"
#include "ResourceManager.h"
#include "Cube.h"
#include <SDL.h>
#include <iostream>
#include <GameTime.h>
#include <iostream>

PyramidCubes::PyramidCubes( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, int size, int wichLevel, int howManuJumpsNeeded )
	: BaseComponent( parentGameObject )
	, m_Size{ size }
	, m_WhichLevel{ wichLevel }
    , m_HowManyJumpsNeeded{ howManuJumpsNeeded }
{
	m_pTexture = texture;

	SetLevel( wichLevel );
}

void PyramidCubes::Update()
{
    for ( const auto& cube : m_pCubes )
    {
        cube->Update();
    }
}

void PyramidCubes::Render() const
{
    for ( const auto& cube : m_pCubes )
    {
        cube->Render();
    }
}

void PyramidCubes::SetLevel( const int level )
{
    m_WhichLevel = level;
    m_pCubes.clear();

    float initialX = 0;
    float initialY = 0;
    //hardcoded bc pixel values
    float offsetX = 30 * m_Scale;
    float offsetY = 23 * m_Scale;

    for ( int levelIndex = 0; levelIndex < m_Size; ++levelIndex )
    {
        float startX = initialX - levelIndex * ( offsetX / 2 );
        float startY = initialY + levelIndex * offsetY;

        for ( int i = 0; i <= levelIndex; ++i )
        {
            float cubeX = startX + i * offsetX;
            float cubeY = startY;

            auto cube = std::make_shared<Cube>( GetOwner(), m_pTexture, m_Scale, m_WhichLevel, m_HowManyJumpsNeeded );
            cube->SetLocalPosition( cubeX, cubeY );

            m_pCubes.push_back( cube );
            GetOwner()->AddComponent( cube );
        }
    }

    m_EndGoalCube = std::make_shared<Cube>( GetOwner(), m_pTexture, m_Scale, m_WhichLevel, m_HowManyJumpsNeeded );
    m_EndGoalCube->SetLocalPosition( 245, -45 );
    m_EndGoalCube->CompletedCube();
}

void PyramidCubes::CompleteLevel()
{
    for ( auto& cube : m_pCubes )
    {
        cube->Won();
	}
}

void PyramidCubes::ResetLevel()
{
    for ( auto& cube : m_pCubes )
    {
        cube->Reset();
    }
    m_CompletedCubes = 0;
    ResetIndex1();
    ResetIndex2();
}

void PyramidCubes::ResetIndex1()
{
    m_CanMove = true;
    m_QBert1ColIndex = 1;
    m_QBert1RowIndex = 0;
}

void PyramidCubes::ResetIndex2()
{
	m_CanMove = true;
	m_QBert2ColIndex = 1;
	m_QBert2RowIndex = 0;
}

void PyramidCubes::GameOver()
{
    m_CanMove = false;
}

void PyramidCubes::WalkedOnCube( SingleMovementComponent::Direction dir, int wichplayer)
{
    if( !m_CanMove ) return;

    if ( wichplayer == 1 )
    {
        int oldActiveCol = m_QBert1ColIndex;
        switch ( dir )
        {
        case SingleMovementComponent::Direction::LeftUp:
            m_QBert1RowIndex -= oldActiveCol;
            m_QBert1ColIndex -= 1;
            break;
        case SingleMovementComponent::Direction::RightDown:
            m_QBert1RowIndex += oldActiveCol + 1;
            m_QBert1ColIndex += 1;
            break;
        case SingleMovementComponent::Direction::LeftDown:
            m_QBert1RowIndex += oldActiveCol;
            m_QBert1ColIndex += 1;
            break;
        case SingleMovementComponent::Direction::RightUp:
            m_QBert1RowIndex -= oldActiveCol - 1;
            m_QBert1ColIndex -= 1;
            break;
        }

        int rowStartIndex = ( ( m_QBert1ColIndex - 1 ) * ( m_QBert1ColIndex ) ) / 2;
        int rowEndIndex = rowStartIndex + m_QBert1ColIndex - 1;

        if ( ( m_QBert1RowIndex < 0 || m_QBert1ColIndex > m_Size ) || ( m_QBert1RowIndex < rowStartIndex || m_QBert1RowIndex > rowEndIndex ) || m_QBert1ColIndex == 0 )
        {
            //TODO: check for platforms
            NotifyObservers( dae::EventType::PLAYER1_OUT_OF_BOUNDS, GetOwner() );
            return;
        }

        if ( m_QBert1RowIndex >= 0 && unsigned( m_QBert1RowIndex ) < m_pCubes.size() && m_pCubes[ m_QBert1RowIndex ] != nullptr )
        {
            m_pCubes[ m_QBert1RowIndex ]->LandedOnThisCube();
        }
    }
    else 
    {
        int oldActiveCol = m_QBert2ColIndex;
        switch ( dir )
        {
        case SingleMovementComponent::Direction::LeftUp:
            m_QBert2RowIndex -= oldActiveCol;
            m_QBert2ColIndex -= 1;
            break;
        case SingleMovementComponent::Direction::RightDown:
            m_QBert2RowIndex += oldActiveCol + 1;
            m_QBert2ColIndex += 1;
            break;
        case SingleMovementComponent::Direction::LeftDown:
            m_QBert2RowIndex += oldActiveCol;
            m_QBert2ColIndex += 1;
            break;
        case SingleMovementComponent::Direction::RightUp:
            m_QBert2RowIndex -= oldActiveCol - 1;
            m_QBert2ColIndex -= 1;
            break;
        }

        int rowStartIndex = ( ( m_QBert2ColIndex - 1 ) * ( m_QBert2ColIndex ) ) / 2;
        int rowEndIndex = rowStartIndex + m_QBert2ColIndex - 1;

        if ( ( m_QBert2RowIndex < 0 || m_QBert2ColIndex > m_Size ) || ( m_QBert2RowIndex < rowStartIndex || m_QBert2RowIndex > rowEndIndex ) || m_QBert2ColIndex == 0 )
        {
            //TODO: check for platforms
            NotifyObservers( dae::EventType::PLAYER2_OUT_OF_BOUNDS, GetOwner() );
            return;
        }

        if ( m_QBert2RowIndex >= 0 && unsigned( m_QBert2RowIndex ) < m_pCubes.size() && m_pCubes[ m_QBert2RowIndex ] != nullptr )
        {
            m_pCubes[ m_QBert2RowIndex ]->LandedOnThisCube();
        }
    }

    m_CompletedCubes = 0;

    for ( const auto& cube : m_pCubes )
    {
        if ( cube->IsCompleted() )
        {
			m_CompletedCubes += 1;
		}
	}

    if ( unsigned(m_CompletedCubes) == m_pCubes.size() )
    {
        NotifyObservers( dae::EventType::PLAYER_WON, GetOwner() );
    }
}

void PyramidCubes::ReverseCube( int row )
{
    if ( unsigned( row ) < m_pCubes.size() && m_pCubes[ row ] != nullptr )
    {
		m_pCubes[ row ]->ReverseOne();
	}
}

int PyramidCubes::GetActiveRow2() const
{
    if ( this != nullptr )
    {
        if( m_IsCoop )
        {
			return m_QBert2ColIndex;
		}
        else{ return 0; }
    }
    else
    {
        return 0;
    }
}

int PyramidCubes::GetActiveColumn2() const
{
    if ( m_IsCoop )
    {
        return m_QBert2RowIndex;
    }
    else
    {
        return 0;
    }
}

int PyramidCubes::GetRowStartIndex( int col ) const
{
    return ( ( col - 1 ) * ( col ) ) / 2;
}
int PyramidCubes::GetRowEndIndex( int col ) const
{
    return  GetRowStartIndex( col ) + col - 1;
}
void PyramidCubes::KilledEnemy()
{
	NotifyObservers( dae::EventType::KILL_ENEMY, GetOwner() );
}
void PyramidCubes::Player1Hit()
{
	NotifyObservers( dae::EventType::PLAYER1_HIT, GetOwner() );
}
void PyramidCubes::Player2Hit()
{
    NotifyObservers( dae::EventType::PLAYER2_HIT, GetOwner() );
}
void PyramidCubes::PlayerDied()
{
	NotifyObservers( dae::EventType::PLAYER_DIED, GetOwner() );
}
void PyramidCubes::CoilyDead()
{
	NotifyObservers( dae::EventType::COILY_DEAD, GetOwner() );
}
void PyramidCubes::RemovePlayer()
{
	NotifyObservers( dae::EventType::REMOVE_PLAYER, GetOwner() );
    m_IsCoop= false;
}

void PyramidCubes::SetLeftBottom()
{
    for ( int index = 0; index < m_Size - 1; ++index ) 
    {
        int oldActiveCol = m_QBert1ColIndex;

        m_QBert1RowIndex += oldActiveCol;
        m_QBert1ColIndex += 1;
    }

}

void PyramidCubes::SetRightBottom()
{
    for ( int index = 0; index < m_Size - 1; ++index )
    {
        int oldActiveCol = m_QBert2ColIndex;

        m_QBert2RowIndex += oldActiveCol + 1;
        m_QBert2ColIndex += 1;
    }

}

