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

   // float elapsedTime = 0.0f;

    //while ( elapsedTime < 3.0f ) 
    //{

    //    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
    //    elapsedTime += deltaTime;
    //}

    //dae::SceneManager::GetInstance().SetCurrentScene( m_WhichLevel + 2 );
}

void PyramidCubes::WalkedOnCube( SingleMovementComponent::Direction dir)
{
    switch ( dir )
    {
    case SingleMovementComponent::Direction::LeftUp:
        m_QBertCubeIndex -= ( m_ActiveRow);
        m_ActiveRow -= 1;
        break;

    case SingleMovementComponent::Direction::RightDown:
        m_QBertCubeIndex += ( m_ActiveRow + 1 );
        m_ActiveRow += 1;
        break;

    case SingleMovementComponent::Direction::LeftDown:
        m_QBertCubeIndex += m_ActiveRow;
        m_ActiveRow += 1;
        break;

    case SingleMovementComponent::Direction::RightUp:
        m_QBertCubeIndex -= (m_ActiveRow-1);
        m_ActiveRow -= 1;
        break;
    }

    if ( m_QBertCubeIndex >= 0 && m_QBertCubeIndex < m_pCubes.size() && m_pCubes[ m_QBertCubeIndex ] != nullptr )
    {
        m_pCubes[ m_QBertCubeIndex ]->LandedOnThisCube();
    }
    else 
    {
        NotifyObservers(dae::EventType::PLAYER_OUT_OF_BOUNDS, GetOwner() );
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


