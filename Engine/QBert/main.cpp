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

void load()
{
	//MAIN MENU
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene( "MainMenu" );
	auto go = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	go->AddComponent( texture );
	mainMenu.Add( go );

	//PLAYER
	auto Qbert = std::make_shared<dae::GameObject>();
	auto QbertTexture = std::make_shared < dae::TextureComponent>( Qbert.get(), "qbert.png" );
	Qbert->AddComponent( QbertTexture );
	Qbert->AddComponent( std::make_shared<dae::MovenmentComponent>( Qbert.get(), 100.f ) );
	Qbert->SetLocalTransform( { 100.f, 250.f } );
	auto Health = std::make_shared<dae::HealthComponent>( Qbert.get(), 3 );
	Qbert->AddComponent( Health );


	//LEVEL 1
	auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level1" );
	auto goLevel = std::make_shared<dae::GameObject>();
	goLevel->SetLocalTransform( { 300, 140 } );
	auto level = std::make_shared <Level>( goLevel.get(),0,7,0 );
	goLevel->AddComponent( level );
	level1.Add( goLevel );

	//LEVEL 2
	auto& level2 = dae::SceneManager::GetInstance().CreateScene( "Level2" );
	auto goLevel2 = std::make_shared<dae::GameObject>();
	goLevel2->SetLocalTransform( { 300, 140 } );
	auto Level2 = std::make_shared <Level>( goLevel2.get(), 0, 4, 1 );
	goLevel2->AddComponent( Level2 );
	level2.Add( goLevel2 );

	//for debug purposes
	auto levelswitcher = std::make_shared<dae::GameObject>();
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_1, dae::OpenLevelCommand{ levelswitcher.get(), 1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_2, dae::OpenLevelCommand{ levelswitcher.get(), 2 } );
	//

	dae::SceneManager::GetInstance().SetCurrentScene( 1 );
}

int main( int, char* [] ) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}