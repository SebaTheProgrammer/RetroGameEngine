#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include "Scene.h"
#include "PyramidCubes.h"
#include "InputManager.h"
#include "InputCommands.h"
#include "Level.h"
#include "ResourceManager.h"
#include <TextComponent.h>
#include "QBert.h"
#include "PlayerCommands.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "LevelFile.h"
#include "ScoreFile.h"
#include "HighScoreScreen.h"
#include "Commands.h"
#include "ButtonComponent.h"
#include "ButtonManagerComponent.h"
#include "ChangeNameScreen.h"
#include "MainMenuScreen.h"

void load()
{
	//Sound
	dae::ServiceLocator::RegisterSoundSystem( std::make_unique<dae::SDLSoundSystem>() );
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.AddSound( "Start", "Sounds/Start.wav" );
	ss.Play( ss.GetSoundId( "Start" ), 50 );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto font2 = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );

	ScoreFile::GetInstance().ReadName();
	if ( ScoreFile::GetInstance().GetName() == "" )
	{
		ScoreFile::GetInstance().SetName( "Random Player" );
	}

	//MAIN MENU
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene( "MainMenu" );
	auto go = std::make_shared<dae::GameObject>( 0 );
	auto selectionArrow = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Selection Arrow.png" ) };
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga");

	//Resources
	int hp = 4;
	Level::allTextures LevelTextures;
	{
		LevelTextures.m_QbertIdle = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ) };
		LevelTextures.m_QbertBackfaceIdle = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "qbertBackFaceIdle.png" ) };
		LevelTextures.m_Coily = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "SnakePurple.png" ) };
		LevelTextures.m_UggWrongWay = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "UggWrongWay.png" ) };
		LevelTextures.m_Slick = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Slick.png" ) };
		LevelTextures.m_Sam = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Sam.png" ) };
		LevelTextures.m_GameOverTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Game Over Title.png" ) };
		LevelTextures.m_WinTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Victory Title.png" ) };
		LevelTextures.m_CubesTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Qbert Cubes.png" ) };
		LevelTextures.m_DiscTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Disk Spritesheet.png" ) };
	}

	//Level loading from file:
	{
		const std::string path = "../Data/levels.txt";
		LevelFile levelFile( path );
		std::vector<LevelFile::Level> levels = levelFile.ReadLevelFile();
		int size = static_cast< int >( levels.size() );
		int levelgameobjectNumber = 1;
		for ( const auto& level : levels )
		{
			int lentgh = level.length;
			int levelNumber = level.levelNumber;
			int jump = level.howManyJumpsNeeded;

			LevelTextures.m_BgTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "bg" + std::to_string( levelNumber ) + ".png" ) };
			LevelTextures.m_BeginTexture = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Level 0" + std::to_string( jump ) + " Title.png" ) };

			auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level" + level.levelNumber );
			auto goLevel = std::make_shared<dae::GameObject>( levelgameobjectNumber );
			goLevel->SetLocalTransform( { 300, 130 } );
			auto levelComponent = std::make_shared <Level>( goLevel.get(), lentgh, levelNumber, jump, size, LevelTextures, hp );
			goLevel->AddComponent( levelComponent );
			level1.Add( goLevel );
			levelgameobjectNumber += 1;
		}
	}

	//HIGHSCORE
	auto& highScore = dae::SceneManager::GetInstance().CreateScene( "Highscores" );
	int max = static_cast< int >( dae::SceneManager::GetInstance().GetMaxScenes() - 1 );
	auto score = std::make_shared<dae::GameObject>( max );
	auto highscore = std::make_shared<HighScoreScreen>( score.get(), selectionArrow, font, font2 );
	score->AddComponent( highscore );
	highScore.Add( score );

	//Levelswitcher
	auto levelswitcher = std::make_shared<dae::GameObject>( -1 );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_F1, InputTypeKeyBoard::IsDownThisFrame, dae::OpenNextLevelCommand{ levelswitcher.get() } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_M, InputTypeKeyBoard::IsDownThisFrame, SoundCommand{} );

	//ChangeNameScreen
	auto& changeNameScene = dae::SceneManager::GetInstance().CreateScene( "ChangeName" );
	max = static_cast< int >( dae::SceneManager::GetInstance().GetMaxScenes() - 1 );
	auto screenOb = std::make_shared<dae::GameObject>( max );
	auto changeNameScreen = std::make_shared < ChangeNameScreen>( screenOb.get(), selectionArrow, font );
	screenOb->AddComponent( texture );
	screenOb->AddComponent( changeNameScreen );
	changeNameScene.Add( screenOb );

	auto menu = std::make_shared < MainMenuScreen >( go.get(), selectionArrow, font, highscore.get(), max);
	go->AddComponent( menu );
	mainMenu.Add( go );

	dae::SceneManager::GetInstance().SetCurrentScene( 0 );

	std::cout << "!Welcome " << ScoreFile::GetInstance().GetName() << " and enjoy QBert!" << std::endl;
	std::cout << "Made by Vryens Sebastiaan, 2GD18 " << std::endl;
}

int main( int, char* [] ) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}