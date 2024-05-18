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
#include "ScoreComponent.h"

LevelHandeler::LevelHandeler( dae::GameObject* parentGameObject, int& lives ):
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
		if ( dae::ScoreComponent * scoreComponent{ GetOwner()->GetComponent< dae::ScoreComponent>().get() } )
		{
			scoreComponent->SetScore( m_Score );
		}
		m_NeedsUpdate = false;
	}

	if ( m_Completed )
	{
		ChangeLevel();
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
		m_pQbert->SetCanMove( false );
		m_Completed = true;
		break;

	case dae::EventType::PLAYER_MOVED:
		if ( QBert * qbert{ gameObj->GetComponent<QBert>().get() } )
		{
			m_pQbert = qbert;
			GetOwner()->GetComponent<PyramidCubes>()->WalkedOnCube( qbert->GetDirection() );
		}
		break;

	case dae::EventType::NEW_CUBE_COMPLETED:
		m_Score += 15;
		m_NeedsUpdate = true;
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
	m_Lives = lives;
	m_NeedsUpdate = true;
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

void LevelHandeler::ChangeLevel()
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
			
			for ( int index{}; index < dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects().size(); ++index )
			{
				if ( dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects()[ index ]->GetComponent<LevelHandeler>() != nullptr )
				{
					dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects()[ index ]->GetComponent<LevelHandeler>()->SetLives( m_Lives );
					dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects()[ index ]->GetComponent<LevelHandeler>()->SetScore( m_Score );
				}
			}
		}
		else
		{
			//TODO:: Win screen then go to main menu
			dae::SceneManager::GetInstance().SetCurrentScene( 0 );
		}

		m_EndTimer = 0.0f;
		m_Completed = false;
	}
}
