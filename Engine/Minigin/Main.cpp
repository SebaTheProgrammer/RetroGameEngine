#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "TransformCircleComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "InputCommands.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene( "Demo" );

	//bg
	auto go = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	go->AddComponent( texture );
	scene.Add( go );

	//logo
	auto go2 = std::make_shared<dae::GameObject>();
	texture = std::make_shared < dae::TextureComponent>( go2.get(), "logo.tga" );
	go2->AddComponent( texture );
	go2->SetLocalTransform( {216, 180} );
	scene.Add(go2);

	//fps counter
	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto go3 = std::make_shared<dae::GameObject>();
	go3->AddComponent( std::make_shared<dae::FPSComponent>( go3.get(), "0 FPS", font ) );
	go3->SetLocalTransform( { 80, 10 } );
	scene.Add( go3 );

	//Qbert
	auto Qbert = std::make_shared<dae::GameObject>();
	auto QbertTexture = std::make_shared < dae::TextureComponent>( Qbert.get(), "qbert.png" );
	Qbert->AddComponent( QbertTexture );
	Qbert->AddComponent( std::make_shared<dae::MovenmentComponent>( Qbert.get(), 100.f ) );
	Qbert->SetLocalTransform( { 100.f, 250.f } );

	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{0.f, -1.f} } );
	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{-1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{0.f, 1.f} } );
	scene.Add( Qbert );

	//2nd Qbert
	auto Qbert2 = std::make_shared<dae::GameObject>();
	auto QbertTexture2 = std::make_shared < dae::TextureComponent>( Qbert2.get(), "qbert.png" );
	Qbert2->AddComponent( QbertTexture2 );
	Qbert2->AddComponent( std::make_shared<dae::MovenmentComponent>( Qbert2.get(), 200.f ) );
	Qbert2->SetLocalTransform( { 350.f, 250.f } );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, dae::MoveCommand{ Qbert2.get(), glm::vec2{0.f, -1.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, dae::MoveCommand{ Qbert2.get(), glm::vec2{-1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, dae::MoveCommand{ Qbert2.get(), glm::vec2{0.f, 1.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, dae::MoveCommand{ Qbert2.get(), glm::vec2{1.f, 0.f} } );
	scene.Add( Qbert2 );
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}