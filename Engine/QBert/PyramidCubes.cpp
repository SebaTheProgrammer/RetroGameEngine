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
    ResetIndex();
}

void PyramidCubes::ResetIndex()
{
    m_CanMove = true;
    m_QBertColIndex = 1;
    m_QBertRowIndex = 0;
}

void PyramidCubes::GameOver()
{
    m_CanMove = false;
}

void PyramidCubes::WalkedOnCube( SingleMovementComponent::Direction dir)
{
    if( !m_CanMove ) return;

    int oldActiveCol = m_QBertColIndex;
    // Update cube index and active row based on movement direction
    switch (dir) 
    {
        case SingleMovementComponent::Direction::LeftUp:
            m_QBertRowIndex -= oldActiveCol;
            m_QBertColIndex -= 1;
            break;
        case SingleMovementComponent::Direction::RightDown:
            m_QBertRowIndex += oldActiveCol + 1;
            m_QBertColIndex += 1;
            break;
        case SingleMovementComponent::Direction::LeftDown:
            m_QBertRowIndex += oldActiveCol;
            m_QBertColIndex += 1;
            break;
        case SingleMovementComponent::Direction::RightUp:
            m_QBertRowIndex -= oldActiveCol - 1;
            m_QBertColIndex -= 1;
            break;
    }

    int rowStartIndex = ( (m_QBertColIndex-1) * ( m_QBertColIndex)) / 2;
    int rowEndIndex = rowStartIndex + m_QBertColIndex-1;

    if ( (m_QBertRowIndex < 0 || m_QBertColIndex > m_Size) || (m_QBertRowIndex < rowStartIndex || m_QBertRowIndex > rowEndIndex) || m_QBertColIndex == 0)
    {
        //TODO: check for platforms
        NotifyObservers(dae::EventType::PLAYER_OUT_OF_BOUNDS, GetOwner());
        return;
    }

    if ( m_QBertRowIndex >= 0 && unsigned(m_QBertRowIndex) < m_pCubes.size() && m_pCubes[ m_QBertRowIndex ] != nullptr )
    {
        m_pCubes[ m_QBertRowIndex ]->LandedOnThisCube();
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

void PyramidCubes::KilledEnemy()
{
	NotifyObservers( dae::EventType::KILL_ENEMY, GetOwner() );
}

void PyramidCubes::PlayerHit()
{
	NotifyObservers( dae::EventType::PLAYER_HIT, GetOwner() );
}

void PyramidCubes::PlayerDied()
{
	NotifyObservers( dae::EventType::PLAYER_DIED, GetOwner() );
}

