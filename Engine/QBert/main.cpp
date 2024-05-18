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

void load()
{
	//Sound
	dae::ServiceLocator::RegisterSoundSystem( std::make_unique<dae::SDLSoundSystem>() );
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play( 1, 100.f );

	//MAIN MENU
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene( "MainMenu" );
	auto go = std::make_shared<dae::GameObject>(0);
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	auto title = std::make_shared < dae::TextureComponent>( go.get(), "Game Title.png" );
	title->SetLocalPosition( 80, 50 );
	go->AddComponent( texture );
	go->AddComponent( title );
	mainMenu.Add( go );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto font2 = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );
	auto text = std::make_shared<dae::GameObject>( 0 );
	text->AddComponent( std::make_shared<dae::TextComponent>( text.get(), "Main Menu", font ) );
	text->SetLocalTransform( { 10, 210 } );
	mainMenu.Add( text );

	auto text2 = std::make_shared<dae::GameObject>( 0 );
	text2->AddComponent( std::make_shared<dae::TextComponent>( text2.get(), "Press 1 to begin the game", font2 ) );
	text2->SetLocalTransform( { 10, 280 } );
	mainMenu.Add( text2 );

	auto text3 = std::make_shared<dae::GameObject>( 0 );
	text3->AddComponent( std::make_shared<dae::TextComponent>( text3.get(), "Hold WASD to move, you can complete the level and/or die", font2 ) );
	text3->SetLocalTransform( { 10, 310 } );
	mainMenu.Add( text3 );

	//qbert
	int hp = 4;
	auto idle = std::shared_ptr<dae::Texture2D> { dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ) };
	auto backFaceIdle = std::shared_ptr<dae::Texture2D> { dae::ResourceManager::GetInstance().LoadTexture( "qbertBackFaceIdle.png" ) };	

	//Level loading from file:
	const std::string path = "../Data/levels.txt";
	LevelFile levelFile( path );
	std::vector<LevelFile::Level> levels = levelFile.ReadLevelFile();

	for ( const auto& level : levels )
	{
		int lentgh = level.length;
		int levelNumber = level.levelNumber;

		auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level"+ level.levelNumber );
		auto goLevel = std::make_shared<dae::GameObject>( level.levelNumber );
		goLevel->SetLocalTransform( { 300, 130 } );
		auto levelComponent = std::make_shared <Level>( goLevel.get(), lentgh, levelNumber, idle, backFaceIdle, hp );
		goLevel->AddComponent( levelComponent );
		level1.Add( goLevel );
	}

	//for debug purposes
	auto levelswitcher = std::make_shared<dae::GameObject>(-1);
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_1, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 1 } );

	dae::SceneManager::GetInstance().SetCurrentScene( 0 );
}

int main( int, char* [] ) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}