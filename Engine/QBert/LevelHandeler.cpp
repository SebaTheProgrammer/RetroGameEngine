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
#include <ServiceLocator.h>
#include "SoundManager.h"
#include "MainMenuScreen.h"

LevelHandeler::LevelHandeler( dae::GameObject* parentGameObject, int& lives, int maxLevels ):
	BaseComponent( parentGameObject ),
	m_Lives1( lives ), m_Lives2(lives), m_Score(0), m_StartLives( lives ), m_MaxLevels( maxLevels )
{
	
}

void LevelHandeler::Update()
{
	if ( m_NeedsUpdate )
	{
		std::vector<std::shared_ptr<HealthComponentQbert>> m_HealthComponents = GetOwner()->GetComponents<HealthComponentQbert>();

		for ( const auto& healthComponent : m_HealthComponents )
		{
			if ( healthComponent->GetWhichPlayer() == 1 )
			{
				healthComponent->SetLives( m_Lives1 );
			}
			if ( healthComponent->GetWhichPlayer() == 2 )
			{
				healthComponent->SetLives( m_Lives2 );
			}
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
	size_t maxScenes = dae::SceneManager::GetInstance().GetMaxScenes();

	switch ( event )
	{
	case dae::EventType::PLAYER_DIED:

		if ( m_pQbert )
		{
			m_pQbert->ResetPosition();
		}

		if ( m_pQbert2 )
		{
			m_pQbert2->ResetPosition();
		}

		GetOwner()->GetComponent<PyramidCubes>()->ResetIndex1();
		GetOwner()->GetComponent<PyramidCubes>()->ResetIndex2();
		GetOwner()->GetComponent<Level>()->GameOver( m_Score );
		Notify( dae::EventType::LEVEL_RESTART, gameObj );

		break;
	case dae::EventType::COILY_DEAD:

		SoundManager::GetInstance().CoilyFall( m_Volume );
		GetOwner()->GetComponent<Level>()->CoilyDied();
		m_Score += m_ScoreCoily;

		break;

	case dae::EventType::PLAYER1_ON_DISC:
		SoundManager::GetInstance().OnDisc( m_Volume );
		GetOwner()->GetComponent<Level>()->Player1OnDisc();

		break;

	case dae::EventType::PLAYER2_ON_DISC:

		GetOwner()->GetComponent<Level>()->Player2OnDisc();

		break;

	case dae::EventType::PLAYER1_OUT_OF_BOUNDS:
		SoundManager::GetInstance().PlayQbertFall( m_Volume );

		Notify( dae::EventType::PLAYER1_HIT, gameObj );
		break;

	case dae::EventType::PLAYER2_OUT_OF_BOUNDS:
		SoundManager::GetInstance().PlayQbertFall( m_Volume );

		Notify( dae::EventType::PLAYER2_HIT, gameObj );
		break;

	case dae::EventType::PLAYER1_HIT:
		if ( m_Lives1 > 1 )
		{
			SoundManager::GetInstance().PlayerHit( m_Volume );

			--m_Lives1;
			if ( m_Score > m_ScoreCube ) { m_Score -= m_ScoreCube; }
			if ( m_pQbert ) {
				m_pQbert->ResetPosition();
			}
			GetOwner()->GetComponent<PyramidCubes>()->ResetIndex1();
			GetOwner()->GetComponent<Level>()->SetBottomLeft();
			m_NeedsUpdate = true;
		}
		else
		{
			m_Lives1 = 0;
			Notify( dae::EventType::PLAYER_DIED, gameObj );
		}
		break;

	case dae::EventType::PLAYER2_HIT:
		if ( m_Lives2 > 1 )
		{
			SoundManager::GetInstance().PlayerHit( m_Volume );

			--m_Lives2;
			if ( m_Score > m_ScoreCube ) { m_Score -= m_ScoreCube; }

			if ( m_pQbert2 ) {
				m_pQbert2->ResetPosition();
			}
			GetOwner()->GetComponent<PyramidCubes>()->ResetIndex2();
			GetOwner()->GetComponent<Level>()->SetBottomRight();
			m_NeedsUpdate = true;
		}
		else
		{
			m_Lives2 = 0;
			Notify( dae::EventType::PLAYER_DIED, gameObj );
		}
		break;

	case dae::EventType::KILL_ENEMY:
		m_Score += m_ScoreSlickSam;
		SoundManager::GetInstance().CaughtEnemy( m_Volume );
		break;

	case dae::EventType::PLAYER_WON:
		SoundManager::GetInstance().CompleteRound( m_Volume );

		GetOwner()->GetComponent<PyramidCubes>()->CompleteLevel();
		GetOwner()->GetComponent<Level>()->CompletedLevel();
		m_CompletedLevel = true;
		break;

	case dae::EventType::PLAYER_MOVED:
		if ( auto qbert = gameObj->GetComponent<QBert>() )
		{
			SoundManager::GetInstance().PlayerJump( m_Volume );

			if ( qbert->GetWichPlayer() == 1 )
			{
				m_pQbert = qbert;
				GetOwner()->GetComponent<Level>()->Player1Moved();
			}
			else
			{
				m_pQbert2 = qbert;
				GetOwner()->GetComponent<Level>()->Player2Moved();
			}
			GetOwner()->GetComponent<PyramidCubes>()->WalkedOnCube( qbert->GetDirection(), qbert->GetWichPlayer(), GetOwner()->GetComponent<Level>()->GetDiscPos() );
		}
		break;

	case dae::EventType::NEW_CUBE_COMPLETED:
		m_Score += m_ScoreCube;
		break;

	case dae::EventType::DISC_FLOAT_TO_TOP:
		SoundManager::GetInstance().DiscLand( m_Volume );
		GetOwner()->GetComponent<Level>()->SetTop();
		break;

	case dae::EventType::LEVEL_RESTART:
		for ( unsigned i = 0; i < maxScenes; ++i )
		{
			for ( unsigned index{}; index < dae::SceneManager::GetInstance().GetScene( i )->GetObjects().size(); ++index )
			{
				if ( dae::SceneManager::GetInstance().GetScene( i )->GetObjects()[ index ]->GetComponent<LevelHandeler>() != nullptr )
				{
					dae::SceneManager::GetInstance().GetScene( i )->GetObjects()[ index ]->GetComponent<LevelHandeler>()->ResetLevel();
				}
			}
		}
		dae::SceneManager::GetInstance().SetCurrentScene( 0 );
		for ( auto& object : dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects() )
		{
			auto menu = object->GetComponent<MainMenuScreen>();
			if ( menu )
			{
				menu->AssignControllerInput();
			}
		}

		ResetLevel();
		break;
	case dae::EventType::REMOVE_PLAYER:
		m_pQbert2 = nullptr;
		break;
	}

	m_NeedsUpdate = true;
}

void LevelHandeler::SetLives( int lives )
{	
	m_Lives1 = lives;
	m_NeedsUpdate = true;
}
void LevelHandeler::SetScore( int score )
{
	m_NeedsUpdate = true;
	m_Score = score;
}
int LevelHandeler::GetLives1() const
{	
	return m_Lives1;
}
int LevelHandeler::GetLives2() const
{
	return m_Lives2;
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
		m_Score += int(GetOwner()->GetComponent<Level>()->GetDiscPos().size() * m_ScoreDisc);

		if ( nextscene < m_MaxLevels )
		{
			dae::SceneManager::GetInstance().SetCurrentScene( nextscene );
			
			for ( unsigned index{}; index < dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects().size(); ++index )
			{
				if ( dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects()[ index ]->GetComponent<LevelHandeler>() != nullptr )
				{
					dae::SceneManager::GetInstance().GetCurrentScene()->GetObjects()[ index ]->GetComponent<LevelHandeler>()->SetLives( m_Lives1 );
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
	m_Lives1 = m_StartLives;
	m_Score = 0;
	m_NeedsUpdate = true;
	m_CompletedLevel = false;
	m_EndTimer = 0.0f;
	GetOwner()->GetComponent<PyramidCubes>()->ResetLevel();
	GetOwner()->GetComponent<Level>()->RestartLevel();

	if ( m_pQbert )
	{
		m_pQbert->ResetQBert();
	}

	if ( m_pQbert2 )
	{
		m_pQbert2->ResetQBert();
	}
}
