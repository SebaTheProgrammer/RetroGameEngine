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

void load()
{
	//Sound
	dae::ServiceLocator::RegisterSoundSystem( std::make_unique<dae::SDLSoundSystem>() );
	auto clip = std::make_shared < dae::AudioClip>( "../Data/Sounds/Level_Screen_Tune.wav" );
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.AddAudioClip( 1, clip );
	ss.Play( 1, 100.f );


	//MAIN MENU
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene( "MainMenu" );
	auto go = std::make_shared<dae::GameObject>(0);
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	go->AddComponent( texture );
	mainMenu.Add( go );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto font2 = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );
	auto text = std::make_shared<dae::GameObject>( 0 );
	text->AddComponent( std::make_shared<dae::TextComponent>( text.get(), "Main Menu", font ) );
	text->SetLocalTransform( { 10, 10 } );
	mainMenu.Add( text );

	auto text2 = std::make_shared<dae::GameObject>( 0 );
	text2->AddComponent( std::make_shared<dae::TextComponent>( text2.get(), "Press 0 (menu), 1, 2 or 3 to switch level (debug purposes)", font2 ) );
	text2->SetLocalTransform( { 10, 80 } );
	mainMenu.Add( text2 );

	auto text3 = std::make_shared<dae::GameObject>( 0 );
	text3->AddComponent( std::make_shared<dae::TextComponent>( text3.get(), "Hold WASD to move, you can complete the level and/or die", font2 ) );
	text3->SetLocalTransform( { 10, 110 } );
	mainMenu.Add( text3 );

	//SHOULD I MAKE THIS LIKE THIS? One baselevel component? Or add 1000 things here?

	//LEVEL 1
	auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level1" );
	auto goLevel = std::make_shared<dae::GameObject>(1);
	goLevel->SetLocalTransform( { 300, 130 } );
	auto level = std::make_shared <Level>( goLevel.get(),false,5,0 );
	goLevel->AddComponent( level );
	level1.Add( goLevel );

	//LEVEL 2
	auto& level2 = dae::SceneManager::GetInstance().CreateScene( "Level2" );
	auto goLevel2 = std::make_shared<dae::GameObject>(2);
	goLevel2->SetLocalTransform( { 300, 130 } );
	auto Level2 = std::make_shared <Level>( goLevel2.get(), false, 7, 1 );
	goLevel2->AddComponent( Level2 );
	level2.Add( goLevel2 );

	//LEVEL 3
	auto& level3 = dae::SceneManager::GetInstance().CreateScene( "Level3" );
	auto goLevel3 = std::make_shared<dae::GameObject>(3);
	goLevel3->SetLocalTransform( { 300, 130 } );
	auto Level3 = std::make_shared <Level>( goLevel3.get(), false, 7, 2 );
	goLevel3->AddComponent( Level3 );
	level3.Add( goLevel3 );

	//for debug purposes
	auto levelswitcher = std::make_shared<dae::GameObject>(-1);
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_1, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_2, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 2 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_3, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 3 } );
	//

	dae::SceneManager::GetInstance().SetCurrentScene( 0 );
}

int main( int, char* [] ) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}