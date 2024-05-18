#include "PyramidCubes.h"
#include "ResourceManager.h"
#include "Cube.h"
#include <SDL.h>
#include <iostream>
#include <GameTime.h>

PyramidCubes::PyramidCubes( dae::GameObject* parentGameObject, int size, int wichLevel )
	: BaseComponent( parentGameObject )
	, m_Size{ size }
	, m_WhichLevel{ wichLevel }
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture("Qbert Cubes.png");

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

            auto cube = std::make_shared<Cube>( GetOwner(), m_pTexture, m_Scale, m_WhichLevel );
            cube->SetLocalPosition( cubeX, cubeY );

            m_pCubes.push_back( cube );
            GetOwner()->AddComponent( cube );
        }
    }
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

    ResetIndex();
}

void PyramidCubes::ResetIndex()
{
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

    int oldActiveRow = m_QBertColIndex;

    // Update cube index and active row based on movement direction
    switch (dir) 
    {
        case SingleMovementComponent::Direction::LeftUp:
            m_QBertRowIndex -= oldActiveRow;
            m_QBertColIndex -= 1;
            break;
        case SingleMovementComponent::Direction::RightDown:
            m_QBertRowIndex += oldActiveRow + 1;
            m_QBertColIndex += 1;
            break;
        case SingleMovementComponent::Direction::LeftDown:
            m_QBertRowIndex += oldActiveRow;
            m_QBertColIndex += 1;
            break;
        case SingleMovementComponent::Direction::RightUp:
            m_QBertRowIndex -= oldActiveRow - 1;
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

    if ( m_QBertRowIndex >= 0 && m_QBertRowIndex < m_pCubes.size() && m_pCubes[ m_QBertRowIndex ] != nullptr )
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

    if ( m_CompletedCubes == m_pCubes.size() ) 
    {
        NotifyObservers( dae::EventType::PLAYER_WON, GetOwner() );
    }
}

