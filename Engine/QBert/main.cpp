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

void load()
{
	//Sound
	dae::ServiceLocator::RegisterSoundSystem( std::make_unique<dae::SDLSoundSystem>() );
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.AddSound( "Start", "Sounds/Start.wav" );
	ss.Play( ss.GetSoundId( "Start" ), 50 );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto font2 = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );

	//MAIN MENU
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene( "MainMenu" );
	auto go = std::make_shared<dae::GameObject>( 0 );
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	auto title = std::make_shared < dae::TextureComponent>( go.get(), "Game Title.png" );
	title->SetLocalPosition( 80, 10 );
	go->AddComponent( texture );
	go->AddComponent( title );
	mainMenu.Add( go );

	//ChangeNameScreen
	auto selectionArrow = std::shared_ptr<dae::Texture2D>{ dae::ResourceManager::GetInstance().LoadTexture( "Selection Arrow.png" ) };
	auto& changeNameScene = dae::SceneManager::GetInstance().CreateScene( "ChangeName" );
	auto screenOb = std::make_shared<dae::GameObject>( 1 );
	auto changeNameScreen = std::make_shared < ChangeNameScreen>( screenOb.get(), selectionArrow, font );
	screenOb->AddComponent( texture );
	screenOb->AddComponent( changeNameScreen );
	changeNameScene.Add( screenOb );

	//buttons
	ScoreFile::GetInstance().ReadName();

	auto changeNameGo = std::make_shared<dae::GameObject>( 0 );
	std::shared_ptr<dae::Command> myCommand = std::make_shared< OpenSceneWithIndex>( changeNameGo.get(), 1 );
	auto buttonChangeName = std::make_shared<dae::ButtonComponent>( changeNameGo.get(), "Player: " + ScoreFile::GetInstance().GetName(), font, myCommand);
	changeNameGo->SetLocalTransform( {(640-buttonChangeName->GetTextComponent()->GetTexture()->GetWidth())/2, 185 } );
	changeNameGo->AddComponent( buttonChangeName );
	mainMenu.Add( changeNameGo );

	auto buttonGo = std::make_shared<dae::GameObject>( 0 );
	//std::shared_ptr<dae::Command> myCommand = std::make_shared< SinglePlayer>( buttonGo.get() );
	auto button = std::make_shared<dae::ButtonComponent>( buttonGo.get(), "Solo", font, myCommand );
	buttonGo->SetLocalTransform( { ( 640 - button->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 250 } );
	buttonGo->AddComponent( button );
	mainMenu.Add( buttonGo );

	auto buttonGo2 = std::make_shared<dae::GameObject>( 0 );
	std::shared_ptr<dae::Command> myCommand2 = std::make_shared< MultiplayerCommand>( buttonGo2.get() );
	auto button2 = std::make_shared<dae::ButtonComponent>( buttonGo2.get(), "Two players", font, myCommand2 );
	buttonGo2->SetLocalTransform( { ( 640 - button2->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 300 } );
	buttonGo2->AddComponent( button2 );
	mainMenu.Add( buttonGo2 );

	auto buttonGo3 = std::make_shared<dae::GameObject>( 0 );
	std::shared_ptr<dae::Command> myCommand3 = std::make_shared<VersusCommand>( buttonGo3.get() );
	auto button3 = std::make_shared<dae::ButtonComponent>( buttonGo3.get(), "Versus", font, myCommand3 );
	buttonGo3->SetLocalTransform( { ( 640 - button3->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 350 } );
	buttonGo3->AddComponent( button3 );
	mainMenu.Add( buttonGo3 );

	//ButtonSwitching
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsDownThisFrame, dae::PreviousButtonCommand{ buttonGo.get() } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsDownThisFrame, dae::NextButtonCommand{ buttonGo.get() } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_SPACE, InputTypeKeyBoard::IsDownThisFrame, dae::PressButtonCommand{ buttonGo.get() } );

	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ buttonGo.get() } );
	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ buttonGo.get() } );
	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ buttonGo.get() } );

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

	std::cout << "!Welcome "<<ScoreFile::GetInstance().GetName() <<" and enjoy QBert!" << std::endl;
	std::cout << "Made by Vryens Sebastiaan, 2GD18 " << std::endl;

	auto levelswitcher = std::make_shared<dae::GameObject>( -1 );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_F1, InputTypeKeyBoard::IsDownThisFrame, dae::OpenNextLevelCommand{ levelswitcher.get() } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_M, InputTypeKeyBoard::IsDownThisFrame, SoundCommand{} );

	auto buttonGo4 = std::make_shared<dae::GameObject>( 0 );
	std::shared_ptr<dae::Command> myCommand4 = std::make_shared< OpenHighScoreCommand>( buttonGo4.get(), max, highscore.get() );
	auto button4 = std::make_shared<dae::ButtonComponent>( buttonGo4.get(), "Highscores", font, myCommand4 );
	buttonGo4->SetLocalTransform( { 225, 400 } );
	buttonGo4->AddComponent( button4 );
	mainMenu.Add( buttonGo4 );

	std::vector<std::shared_ptr<dae::ButtonComponent>> allButtons = { buttonChangeName, button, button2, button3, button4 };
	auto buttonManager = std::make_shared<dae::ButtonManagerComponent>( buttonGo.get(), selectionArrow, allButtons );
	buttonGo->AddComponent( buttonManager );

	dae::SceneManager::GetInstance().SetCurrentScene( 0 );
}

int main( int, char* [] ) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}