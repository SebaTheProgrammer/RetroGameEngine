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
	text2->AddComponent( std::make_shared<dae::TextComponent>( text2.get(), "Press 0 (menu), 1, 2 or 3 to switch level (debug purposes)", font2 ) );
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

	//LEVEL 1
	auto& level1 = dae::SceneManager::GetInstance().CreateScene( "Level1" );
	auto goLevel = std::make_shared<dae::GameObject>(1);
	goLevel->SetLocalTransform( { 300, 130 } );
	auto level = std::make_shared <Level>( goLevel.get(),false,5,1, idle, backFaceIdle, hp );
	goLevel->AddComponent( level );
	level1.Add( goLevel );

	//LEVEL 2
	auto& level2 = dae::SceneManager::GetInstance().CreateScene( "Level2" );
	auto goLevel2 = std::make_shared<dae::GameObject>(2);
	goLevel2->SetLocalTransform( { 300, 130 } );
	auto Level2 = std::make_shared <Level>( goLevel2.get(), false, 7, 2, idle, backFaceIdle, hp );
	goLevel2->AddComponent( Level2 );
	level2.Add( goLevel2 );

	//LEVEL 3
	auto& level3 = dae::SceneManager::GetInstance().CreateScene( "Level3" );
	auto goLevel3 = std::make_shared<dae::GameObject>(3);
	goLevel3->SetLocalTransform( { 300, 130 } );
	auto Level3 = std::make_shared <Level>( goLevel3.get(), false, 7, 3, idle, backFaceIdle, hp );
	goLevel3->AddComponent( Level3 );
	level3.Add( goLevel3 );

	//LEVEL 4
	/*auto& level4 = dae::SceneManager::GetInstance().CreateScene( "Level4" );
	auto golevel4 = std::make_shared<dae::GameObject>( 4 );
	golevel4->SetLocalTransform( { 300, 130 } );
	auto Level4 = std::make_shared <Level>( golevel4.get(), false, 7, 4, idle, backFaceIdle, hp );
	golevel4->AddComponent( Level4 );
	level4.Add( golevel4 );*/

	//for debug purposes
	auto levelswitcher = std::make_shared<dae::GameObject>(-1);
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_0, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 0 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_1, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_2, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 2 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_3, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 3 } );
	//dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_4, InputTypeKeyBoard::IsDownThisFrame, dae::OpenLevelCommand{ levelswitcher.get(), 4 } );
	//

	dae::SceneManager::GetInstance().SetCurrentScene( 0 );
}

int main( int, char* [] ) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}