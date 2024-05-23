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

Level::Level( dae::GameObject* parentGameObject, int howLongLevel, int level, int maxLevels,
	std::shared_ptr<dae::Texture2D> idle, std::shared_ptr<dae::Texture2D> backface, int qbertlives )
	: dae::BaseComponent( parentGameObject )
{
	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;
	m_LevelSize = howLongLevel;
	//bg
	std::string bgFilename = "bg" + std::to_string( level) + ".png";
	auto background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( background );

	//pyramid base
	auto pyramid = std::make_shared<PyramidCubes>( parentGameObject, howLongLevel, level - 1);
	parentGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x,parentGameObject->GetLocalTransform().GetPosition().y } );
	parentGameObject->AddComponent( pyramid );

	//begin
	m_BeginScreenObject = std::make_shared<dae::GameObject>( level);
	std::string beginFilename = "Level 0" + std::to_string( level) + " Title.png";
	auto begin = std::make_shared<dae::TextureComponent>( parentGameObject, beginFilename );
	begin->SetLocalPosition( -begin->GetWidth() / 2+30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - begin->GetHeight() / 2 );
	auto beginBg = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	beginBg->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	m_BeginScreenObject->AddComponent( beginBg );
	m_BeginScreenObject->AddComponent( begin );

	//game over
	m_pGameOverObject = std::make_shared<dae::GameObject>( level);
	auto gameOver = std::make_shared<dae::TextureComponent>( parentGameObject, "Game Over Title.png" );
	gameOver->SetLocalPosition( -gameOver->GetWidth() / 2 + 30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - gameOver->GetHeight() / 2 );
	auto textScore = std::make_shared<dae::TextComponent>( parentGameObject, "SCORE: 0", dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 ), true );
	textScore->SetLocalPosition( 235, 300 );
	m_pGameOverObject->AddComponent( beginBg );
	m_pGameOverObject->AddComponent( gameOver );
	m_pGameOverObject->AddComponent( textScore );

	//win game
	m_pWinObject = std::make_shared<dae::GameObject>( level );
	auto gameWin = std::make_shared<dae::TextureComponent>( parentGameObject, "Victory Title.png" );
	gameWin->SetLocalPosition( -gameWin->GetWidth() / 2 + 30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - gameWin->GetHeight() / 2 );
	m_pWinObject->AddComponent( beginBg );
	m_pWinObject->AddComponent( gameWin );
	m_pWinObject->AddComponent( textScore );

	//players
	 // add 2 players, but is for later
	m_QbertGameObject = std::make_shared<dae::GameObject>( level);
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40 } );
	auto qbert = std::shared_ptr<QBert>{};

	qbert = ( std::make_shared<QBert>( m_QbertGameObject.get(), idle, backface, true) );
	m_QbertGameObject->AddComponent( qbert );

	//Levelhandeler
	auto levelHandeler = std::make_shared<LevelHandeler>( parentGameObject, qbertlives, maxLevels );
	parentGameObject->AddComponent( levelHandeler );

	pyramid->AddObserver( levelHandeler.get() );
	qbert->AddObserver( levelHandeler.get() );
	for ( const auto& cube : pyramid->GetCubes() ) { cube->AddObserver( levelHandeler.get() ); };

	//Health display
	auto healthDisplay = std::make_shared<HealthComponentQbert>( parentGameObject, levelHandeler->GetLives());
	healthDisplay->SetLocalPosition( -250, -90 );
	parentGameObject->AddComponent( healthDisplay );

	//Score
	auto score = std::make_shared<dae::ScoreComponent>( parentGameObject,"Score: ", dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 ) );
	score->SetLocalPosition( 200, -90 );
	parentGameObject->AddComponent( score );

	//Enemies
	m_CoilyGameObject.push_back( std::make_shared<dae::GameObject>( level ) );
	m_CoilyGameObject[0] = std::make_shared<dae::GameObject>(level);
	auto coily = std::make_shared<Coily>( m_CoilyGameObject[0].get(), dae::ResourceManager::GetInstance().LoadTexture("SnakePurple.png"), m_LevelSize );
	m_CoilyGameObject[0]->AddComponent(coily);
	m_CoilyGameObject[0]->SetLocalTransform({ 300, 110 });
	//m_CoilyGameObject.push_back( std::make_shared<dae::GameObject>( level ) );
	//m_CoilyGameObject[ 1 ] = std::make_shared<dae::GameObject>( level );
	//auto coily2 = std::make_shared<Coily>( m_CoilyGameObject[ 1 ].get(), dae::ResourceManager::GetInstance().LoadTexture( "SnakeGreen.png" ) );
	//m_CoilyGameObject[ 1 ]->AddComponent( coily2 );
	//m_CoilyGameObject[ 1 ]->SetLocalTransform( { 300, 290 } );
}

void Level::Update()
{
	switch ( m_CurrentState )
	{

	case LevelState::Begin:

		m_BeginTimer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_BeginTimer > m_BeginTime )
		{
			m_CurrentState = LevelState::Normal;
			m_BeginTimer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
		}
		m_BeginScreenObject->Update();
		break;

	case LevelState::GameOver:

		m_BeginTimer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_BeginTimer > ( m_BeginTime * 2 ) )
		{
			m_CurrentState = LevelState::Normal;
			m_BeginTimer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
			dae::SceneManager::GetInstance().SetCurrentScene( 0 );
		}
		m_pGameOverObject->Update();
		break;

	case LevelState::Win:

		m_BeginTimer += dae::GameTime::GetInstance().GetDeltaTime();

		if ( m_BeginTimer > ( m_BeginTime * 2 ) )
		{
			m_CurrentState = LevelState::Normal;
			m_BeginTimer = 0;
			m_QbertGameObject->GetComponent<QBert>()->SetCanMove( true );
			dae::SceneManager::GetInstance().SetCurrentScene( dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 1 );
		}
		m_pWinObject->Update();
		break;
	}

	m_QbertGameObject->Update();
	
	for ( const auto& coily : m_CoilyGameObject )
	{
		coily->Update();
	}
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
		
		for ( const auto& coily : m_CoilyGameObject )
		{
			coily->Render();
		}
		break;
	}
}

void Level::GameOver(int score)
{
	m_CurrentState = LevelState::GameOver;
	m_BeginTimer = 0;
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
	std::string scoreString = std::to_string( score );
	m_pGameOverObject->GetComponent<dae::TextComponent>()->SetText( { "SCORE: " + scoreString } );

	ScoreFile::GetInstance().UpdateHighScores( score );
}

void Level::WinGame( int score )
{
	//Played All Games Out
	m_CurrentState = LevelState::Win;
	m_BeginTimer = 0;
	m_QbertGameObject->GetComponent<QBert>()->SetCanMove( false );
	std::string scoreString = std::to_string( score );
	m_pWinObject->GetComponent<dae::TextComponent>()->SetText( { "SCORE: " + scoreString } );

	ScoreFile::GetInstance().UpdateHighScores( score );
}
