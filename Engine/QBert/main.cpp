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
	auto go = std::make_shared<dae::GameObject>(0);
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	go->AddComponent( texture );
	mainMenu.Add( go );

	//LEVEL 1
	auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level1" );
	auto goLevel = std::make_shared<dae::GameObject>(1);
	goLevel->SetLocalTransform( { 300, 130 } );
	auto level = std::make_shared <Level>( goLevel.get(),0,5,0 );
	goLevel->AddComponent( level );
	level1.Add( goLevel );

	//LEVEL 2
	auto& level2 = dae::SceneManager::GetInstance().CreateScene( "Level2" );
	auto goLevel2 = std::make_shared<dae::GameObject>(2);
	goLevel2->SetLocalTransform( { 300, 130 } );
	auto Level2 = std::make_shared <Level>( goLevel2.get(), 0, 7, 1 );
	goLevel2->AddComponent( Level2 );
	level2.Add( goLevel2 );

	//LEVEL 3
	auto& level3 = dae::SceneManager::GetInstance().CreateScene( "Level3" );
	auto goLevel3 = std::make_shared<dae::GameObject>(3);
	goLevel3->SetLocalTransform( { 300, 130 } );
	auto Level3 = std::make_shared <Level>( goLevel3.get(), 0, 7, 2 );
	goLevel3->AddComponent( Level3 );
	level3.Add( goLevel3 );

	//for debug purposes
	auto levelswitcher = std::make_shared<dae::GameObject>(-1);
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_1, dae::OpenLevelCommand{ levelswitcher.get(), 1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_2, dae::OpenLevelCommand{ levelswitcher.get(), 2 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_3, dae::OpenLevelCommand{ levelswitcher.get(), 3 } );
	//

	dae::SceneManager::GetInstance().SetCurrentScene( 1 );
}

int main( int, char* [] ) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}