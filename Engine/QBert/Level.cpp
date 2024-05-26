#include "Level.h"
#include "GameObject.h"
#include "PyramidCubes.h"
#include "Qbert.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "AnimatedTextureComponent.h"
#include "PlayerCommands.h"
#include "LevelHandeler.h"
#include <iostream>
#include "HealthComponentQbert.h"
#include <GameTime.h>
#include "ScoreComponent.h"
#include "Cube.h"
#include "ScoreFile.h"
#include "Coily.h"
#include "SlickSam.h"
#include "UggWrongWay.h"

Level::Level( dae::GameObject* parentGameObject, int howLongLevel, int level, int howManuJumpsNeeded, int maxLevels,
	allTextures textures, int qbertlives )
	: dae::BaseComponent( parentGameObject )
{
	m_Textures = textures;

	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;
	m_Level = level;
	m_LevelSize = howLongLevel;
	m_MaxEnemies = level * 2;

	auto background = std::make_shared<dae::TextureComponent>( parentGameObject, m_Textures.m_BgTexture );
	background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( background );
	auto text = std::make_shared<dae::TextComponent>( parentGameObject, "LEVEL " + std::to_string( howManuJumpsNeeded ), dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 ), true );
	text->SetLocalPosition( 535, 30 );
	parentGameObject->AddComponent( text );
	auto textstage = std::make_shared<dae::TextComponent>( parentGameObject, "round " + std::to_string( m_LevelSize-4 ), dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 16 ), true );
	textstage->SetLocalPosition( 540, 60 );
	parentGameObject->AddComponent( textstage );

	//pyramid base
	auto pyramid = std::make_shared<PyramidCubes>( parentGameObject, m_Textures.m_CubesTexture, howLongLevel, level - 1, howManuJumpsNeeded );
	parentGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x,parentGameObject->GetLocalTransform().GetPosition().y } );
	parentGameObject->AddComponent( pyramid );
	m_pPyramidCubes = pyramid;

	//begin
	m_BeginScreenObject = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex());

	auto begin = std::make_shared<dae::TextureComponent>( parentGameObject, m_Textures.m_BeginTexture );
	begin->SetLocalPosition( -begin->GetWidth() / 2+30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - begin->GetHeight() / 2 );
	m_BeginScreenObject->AddComponent( background );
	m_BeginScreenObject->AddComponent( begin );

	//game over
	m_pGameOverObject = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
	auto gameOver = std::make_shared<dae::TextureComponent>( parentGameObject, m_Textures.m_GameOverTexture );
	gameOver->SetLocalPosition( -gameOver->GetWidth() / 2 + 30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - gameOver->GetHeight() / 2 );
	auto textScore = std::make_shared<dae::TextComponent>( parentGameObject, "SCORE: 0", dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 ), true );
	textScore->SetLocalPosition( 235, 300 );
	m_pGameOverObject->AddComponent( background );
	m_pGameOverObject->AddComponent( gameOver );
	m_pGameOverObject->AddComponent( textScore );

	//win game
	m_pWinObject = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
	auto gameWin = std::make_shared<dae::TextureComponent>( m_pWinObject.get(), m_Textures.m_WinTexture );
	gameWin->SetLocalPosition( -gameWin->GetWidth() / 2 + 30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - gameWin->GetHeight() / 2 );
	m_pWinObject->AddComponent( background );
	m_pWinObject->AddComponent( gameWin );
	m_pWinObject->AddComponent( textScore );

	//players
	 // add 2 players, but is for later
	m_QbertGameObject = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40 } );
	auto qbert = std::shared_ptr<QBert>{};

	qbert = ( std::make_shared<QBert>( m_QbertGameObject.get(), m_Textures.m_QbertIdle, m_Textures.m_QbertBackfaceIdle, true) );
	m_QbertGameObject->AddComponent( qbert );

	//Levelhandeler
	auto levelHandeler = std::make_shared<LevelHandeler>( parentGameObject, qbertlives, maxLevels );
	parentGameObject->AddComponent( levelHandeler );

	pyramid->AddObserver( levelHandeler.get() );
	qbert->AddObserver( levelHandeler.get() );
	for ( const auto& cube : pyramid->GetCubes() ) { cube->AddObserver( levelHandeler.get() ); };

	//Health display
	auto healthDisplay = std::make_shared<HealthComponentQbert>( parentGameObject, levelHandeler->GetLives());
	healthDisplay->SetLocalPosition( -250, -100 );
	parentGameObject->AddComponent( healthDisplay );

	//Score
	auto score = std::make_shared<dae::ScoreComponent>( parentGameObject,"Score: ", dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 ) );
	score->SetLocalPosition( -250, -70 );
	parentGameObject->AddComponent( score );

	if ( 5 != m_LevelSize )
	{
		m_CurrentState = LevelState::Normal;
		m_Timer = 0;
		m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
	}
}

void Level::Update()
{
	switch ( m_CurrentState )
	{

	case LevelState::Begin:

		m_Timer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_Timer > m_BeginTime )
		{
			m_CurrentState = LevelState::Normal;
			m_Timer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
		}
		m_BeginScreenObject->Update();
		break;

	case LevelState::GameOver:

		m_Timer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_Timer > ( m_BeginTime * 2 ) )
		{
			m_CurrentState = LevelState::Normal;
			m_Timer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
			dae::SceneManager::GetInstance().SetCurrentScene( 0 );
		}
		m_pGameOverObject->Update();
		break;

	case LevelState::Win:

		m_Timer += dae::GameTime::GetInstance().GetDeltaTime();

		if ( m_Timer > ( m_BeginTime * 2 ) )
		{
			m_CurrentState = LevelState::Normal;
			m_Timer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
			dae::SceneManager::GetInstance().SetCurrentScene( dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 1 );
		}
		m_pWinObject->Update();
		break;

	case LevelState::Normal:

		m_Timer += dae::GameTime::GetInstance().GetDeltaTime();

		for ( const auto& enemy : m_EnemiesGameObjects )
		{
			enemy->Update();

			m_EnemiesGameObjects.erase(
				std::remove_if( m_EnemiesGameObjects.begin(), m_EnemiesGameObjects.end(),
					[]( const std::shared_ptr<dae::GameObject>& enemy ) 
					{
						auto slickSam = enemy->GetComponent<SlickSam>();
						return slickSam != nullptr && !slickSam->IsAlive();
					} ),
				m_EnemiesGameObjects.end() );
		}

		if ( m_Timer > m_SpawnEnemyTime )
		{
			SpawnSlickSam();
			m_Timer = 0;
		}
		break;
	}

	m_QbertGameObject->Update();
}

void Level::Render() const
{
	switch ( m_CurrentState )
	{
	case LevelState::Begin:
		m_BeginScreenObject->Render();
		break;

	case LevelState::GameOver:
		m_pGameOverObject->Render();
		break;

	case LevelState::Win:
		m_pWinObject->Render();
		break;

	case LevelState::Normal:
		m_QbertGameObject->Render();
		for ( const auto& enemy : m_EnemiesGameObjects )
		{
			if ( enemy != nullptr )
			{
				enemy->Render();
			}
		}
		break;
	}
}

void Level::GameOver(int score)
{
	m_CurrentState = LevelState::GameOver;
	m_Timer = 0;
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
	std::string scoreString = std::to_string( score );
	m_pGameOverObject->GetComponent<dae::TextComponent>()->SetText( { "SCORE: " + scoreString } );

	ScoreFile::GetInstance().UpdateHighScores( score );
}

void Level::CompletedLevel()
{
	for ( const auto& enemy : m_EnemiesGameObjects )
	{
		if ( enemy->GetComponent<Coily>() != nullptr ) 
		{
			enemy->GetComponent<Coily>()->SetCanMove( false );
		}
		if ( enemy->GetComponent<SlickSam>() != nullptr ) 
		{
			enemy->GetComponent<SlickSam>()->SetCanMove( false );
		}
	}
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
}

void Level::WinGame( int score )
{
	//Played All Games Out
	m_CurrentState = LevelState::Win;
	m_Timer = 0;
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
	std::string scoreString = std::to_string( score );
	m_pWinObject->GetComponent<dae::TextComponent>()->SetText( { "SCORE: " + scoreString } );
	ScoreFile::GetInstance().UpdateHighScores( score );
	dae::SceneManager::GetInstance().SetCurrentScene( dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 1 );
}

void Level::RestartLevel()
{
	m_CurrentState = LevelState::Begin;
	m_Timer = 0;
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
	m_PlayerMoved = false;
	m_HowManyEnemies = 0;
	m_EnemiesGameObjects.clear();
}

void Level::SpawnCoily()
{
	m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex()) );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
	auto coily = std::make_shared<Coily>( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), m_Textures.m_Coily, m_LevelSize, m_pPyramidCubes.get() );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( coily );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 110 } );
}

void Level::PlayerMoved()
{
	if ( !m_PlayerMoved )
	{
		m_PlayerMoved = true;
		SpawnCoily();
	}
}

void Level::SpawnSlickSam()
{
	if ( m_PlayerMoved )
	{
		if ( m_HowManyEnemies < m_MaxEnemies ) 
		{
			if ( m_pPyramidCubes->GetActiveRow() != 0 ) 
			{
				++m_HowManyEnemies;

				m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
				m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
				auto uggWrongWay = std::make_shared<UggWrongWay>( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), 
					m_Textures.m_UggWrongWay, m_LevelSize, m_pPyramidCubes.get() );
				m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( uggWrongWay );
				m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 110 } );
				bool random = rand() % 2;
				if ( random )
				{
					m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
					auto slick = std::make_shared<SlickSam>
						( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), m_Textures.m_Slick, m_LevelSize, m_pPyramidCubes.get() );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( slick );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 110 } );
				}
				else
				{
					m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
					auto sam = std::make_shared<SlickSam>( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), m_Textures.m_Sam, m_LevelSize, m_pPyramidCubes.get() );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( sam );
					m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 110 } );
				}
			}
		}
	}
}
