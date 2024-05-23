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
#include "ScoreFile.h"
#include "TextureComponent.h"

LevelHandeler::LevelHandeler( dae::GameObject* parentGameObject, int& lives, int maxLevels ):
	BaseComponent( parentGameObject ),
	m_Lives( lives ), m_Score(0), m_StartLives( lives ), m_MaxLevels( maxLevels )
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

	if ( m_CompletedLevel )
	{
		ChangeLevel();
	}
}

void LevelHandeler::Notify( dae::EventType event, dae::GameObject* gameObj )
{

	switch ( event )
	{
	case dae::EventType::PLAYER_DIED:

		GetOwner()->GetComponent<Level>()->GameOver(m_Score);
		Notify( dae::EventType::LEVEL_RESTART, gameObj );

		break;

	case dae::EventType::PLAYER_OUT_OF_BOUNDS:

		Notify( dae::EventType::PLAYER_HIT, gameObj );

		m_pQbert->ResetPosition();
		GetOwner()->GetComponent<PyramidCubes>()->ResetIndex();

		break;

	case dae::EventType::PLAYER_HIT:
		if ( m_Lives > 1 )
		{
			--m_Lives;
			if ( m_Score > 25 ) { m_Score -= 25;}
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
		m_CompletedLevel = true;
		break;

	case dae::EventType::PLAYER_MOVED:
		if ( QBert * qbert{ gameObj->GetComponent<QBert>().get() } )
		{
			m_pQbert = qbert;
			GetOwner()->GetComponent<PyramidCubes>()->WalkedOnCube( qbert->GetDirection() );
			m_QBertRowIndex = GetOwner()->GetComponent<PyramidCubes>()->GetActiveRow();
			m_QBertColIndex = GetOwner()->GetComponent<PyramidCubes>()->GetActiveColumn();
			std::cout<< "Row: " << m_QBertRowIndex << " Col: " << m_QBertColIndex << std::endl;

		}
		break;

	case dae::EventType::NEW_CUBE_COMPLETED:
		m_Score += 25;
		break;

	case dae::EventType::LEVEL_RESTART:
		ResetLevel();
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

		if ( nextscene < m_MaxLevels )
		{
			dae::SceneManager::GetInstance().SetCurrentScene( nextscene );
			
			for ( unsigned index{}; index < dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects().size(); ++index )
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
			//Played Game Out
			GetOwner()->GetComponent<Level>()->WinGame( m_Score );
			ResetLevel();
		}

		m_EndTimer = 0.0f;
		m_CompletedLevel = false;
	}
}

void LevelHandeler::ResetLevel()
{
	m_Lives = m_StartLives;
	m_Score = 0;
	m_NeedsUpdate = true;
	m_CompletedLevel = false;
	m_EndTimer = 0.0f;
	GetOwner()->GetComponent<PyramidCubes>()->ResetLevel();
	m_pQbert->ResetPosition();
}
