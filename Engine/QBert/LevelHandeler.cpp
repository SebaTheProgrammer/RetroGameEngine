#include "LevelHandeler.h"
#include <iostream>
#include "GameObject.h"
#include <TextComponent.h>
#include "QBert.h"
#include "PyramidCubes.h"
#include "Level.h"
#include <GameTime.h>
#include <SceneManager.h>
#include <Scene.h>
#include "HealthComponentQbert.h"

LevelHandeler::LevelHandeler( dae::GameObject* const parentGameObject, int& lives ):
	BaseComponent( parentGameObject ),
	m_Lives( lives ), m_Score(0), m_StartLives( lives )
{
}

LevelHandeler::~LevelHandeler()
{
}

void LevelHandeler::Update()
{
	if ( m_NeedsUpdate )
	{
		if ( HealthComponentQbert * healthComponent{ GetOwner()->GetComponent<HealthComponentQbert>().get()} )
		{
			healthComponent->SetLives( m_Lives );
		}
		m_NeedsUpdate = false;
	}

	if ( m_Completed )
	{
		if ( m_EndTimer < m_EndTimeChangeLevel )
		{
			m_EndTimer += dae::GameTime::GetInstance().GetDeltaTime();
		}
		else
		{
			int nextscene = dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 1;

			if ( nextscene <= dae::SceneManager::GetInstance().GetMaxScenes() )
			{
				dae::SceneManager::GetInstance().SetCurrentScene( nextscene );				
			}
			else
			{
				dae::SceneManager::GetInstance().SetCurrentScene( 0 );
			}

			m_EndTimer= 0.0f;
			m_Completed = false;
		}
	}
}

void LevelHandeler::Notify( dae::EventType event, dae::GameObject* gameObj )
{

	switch ( event )
	{
	case dae::EventType::PLAYER_DIED:

		std::cout << "PLAYER DIED" << std::endl;
		//game over screen
		Notify( dae::EventType::LEVEL_RESTART, gameObj );
		break;

	case dae::EventType::PLAYER_OUT_OF_BOUNDS:

		Notify( dae::EventType::PLAYER_HIT, gameObj );

		m_pQbert->ResetPosition();
		GetOwner()->GetComponent<PyramidCubes>()->ResetIndex();
		break;

	case dae::EventType::PLAYER_HIT:

		m_NeedsUpdate = true;
		if ( m_Lives > 1 )
		{
			--m_Lives;
		}
		else
		{
			m_Lives = 0;
			Notify( dae::EventType::PLAYER_DIED, gameObj );
		}
		break;

	case dae::EventType::KILL_ENEMY:
		m_Score += 100;
		break;

	case dae::EventType::PLAYER_WON:
		GetOwner()->GetComponent<PyramidCubes>()->CompleteLevel();
		m_Completed = true;

		break;

	case dae::EventType::PLAYER_MOVED:
		if ( QBert * qbert{ gameObj->GetComponent<QBert>().get() } )
		{
			m_pQbert = qbert;
			GetOwner()->GetComponent<PyramidCubes>()->WalkedOnCube( qbert->GetDirection() );
		}
		break;

	case dae::EventType::LEVEL_RESTART:
		GetOwner()->GetComponent<PyramidCubes>()->ResetLevel();
		m_Lives = m_StartLives;
		m_Score = 0;
		break;
	}

	m_NeedsUpdate = true;
}

void LevelHandeler::SetLives( int lives )
{	
	m_NeedsUpdate = true;
	m_Lives = lives;
}

void LevelHandeler::SetScore( int score )
{
	m_NeedsUpdate = true;
	m_Score = score;
}

int LevelHandeler::GetLives() const
{	
	return m_Lives;
}

int LevelHandeler::GetScore() const
{
	return m_Score;
}
