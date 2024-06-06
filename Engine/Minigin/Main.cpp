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
#include "HealthComponent.h"
#include "SoundSystem.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene( "Demo" );

	//bg
	auto go = std::make_shared<dae::GameObject>(0);
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga" );
	go->AddComponent( texture );
	scene.Add( go );

	//logo
	auto go2 = std::make_shared<dae::GameObject>(0);
	texture = std::make_shared < dae::TextureComponent>( go2.get(), "logo.tga" );
	go2->AddComponent( texture );
	go2->SetLocalTransform( {216, 180} );
	scene.Add(go2);

	//fps counter
	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto go3 = std::make_shared<dae::GameObject>(0);
	go3->AddComponent( std::make_shared<dae::FPSComponent>( go3.get(), "0 FPS", font ) );
	go3->SetLocalTransform( { 10, 80 } );
	scene.Add( go3 );

	//Text
	auto go4 = std::make_shared<dae::GameObject>(0);
	go4->AddComponent( std::make_shared<dae::TextComponent>( go4.get(), "Programming 4 Assignment", font ) );
	go4->SetLocalTransform( { 10, 10 } );
	scene.Add( go4 );

	auto font2 = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 16 );
	auto go5 = std::make_shared<dae::GameObject>(0);
	go5->AddComponent( std::make_shared<dae::TextComponent>( go5.get(), "Use the D pad to move pacman, x to inflict damage, a and b to pickup pellets", font2 ) );
	go5->SetLocalTransform( { 10, 120 } );
	scene.Add( go5 );

	auto go6 = std::make_shared<dae::GameObject>(0);
	go6->AddComponent( std::make_shared<dae::TextComponent>( go6.get(), "Use the WASD to move pacman, c to inflict damage, z and x to pickup pellets", font2 ) );
	go6->SetLocalTransform( { 10, 140 } );
	scene.Add( go6 );

	//Qbert
	auto Qbert = std::make_shared<dae::GameObject>(0);
	auto QbertTexture = std::make_shared < dae::TextureComponent>( Qbert.get(), "qbert.png" );
	Qbert->AddComponent( QbertTexture );
	Qbert->AddComponent( std::make_shared<dae::MovenmentComponent>( Qbert.get(), 100.f ) );
	Qbert->SetLocalTransform( { 100.f, 250.f } );

	auto Health = std::make_shared<dae::HealthComponent>( Qbert.get(), 5 );
	Qbert->AddComponent( Health );

	auto textQbert = std::make_shared<dae::GameObject>(0);
	auto text = std::make_shared<dae::TextComponent>( textQbert.get(), "Health: " + std::to_string( Health->GetHealth() ), font2 );
	textQbert->AddComponent( text );
	textQbert->SetLocalTransform( { 10.f, 200.f } );
	scene.Add( textQbert );

	dae::InputManager::GetInstance().BindActionGamePad(0,XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{0.f, -1.f} } );
	dae::InputManager::GetInstance().BindActionGamePad(0,XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{-1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionGamePad(0,XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionGamePad(0,XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed, dae::MoveCommand{ Qbert.get(), glm::vec2{0.f, 1.f} } );
	scene.Add( Qbert );

	//2nd Qbert
	auto Qbert2 = std::make_shared<dae::GameObject>(0);
	auto QbertTexture2 = std::make_shared < dae::TextureComponent>( Qbert2.get(), "qbert.png" );
	Qbert2->AddComponent( QbertTexture2 );
	Qbert2->AddComponent( std::make_shared<dae::MovenmentComponent>( Qbert2.get(), 200.f ) );
	Qbert2->SetLocalTransform( { 350.f, 250.f } );

	auto Health2 = std::make_shared<dae::HealthComponent>( Qbert2.get(), 3 );
	Qbert2->AddComponent( Health2 );

	auto textQbert2 = std::make_shared<dae::GameObject>(0);
	auto text2 = std::make_shared<dae::TextComponent>( textQbert2.get(), "Health: " + std::to_string( Health2->GetHealth() ), font2 );
	textQbert2->AddComponent( text2 );
	textQbert2->SetLocalTransform( { 10.f, 260.f } );
	//text2->GetOnTextChangedEvent().AddCallback( { text2->SetText( "Health: " + std::to_string( Health2->GetHealth() ) ) } );
	scene.Add( textQbert2 );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_C, InputTypeKeyBoard::IsPressed, dae::DealDamageCommand{Qbert2.get(), 1});
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_X, InputTypeKeyBoard::IsPressed, dae::AddScoreCommand{ Qbert2.get(), 1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_Z, InputTypeKeyBoard::IsPressed, dae::AddScoreCommand{ Qbert2.get(), 10 } );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsPressed, dae::MoveCommand{ Qbert2.get(), glm::vec2{0.f, -1.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, InputTypeKeyBoard::IsPressed, dae::MoveCommand{ Qbert2.get(), glm::vec2{-1.f, 0.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsPressed, dae::MoveCommand{ Qbert2.get(), glm::vec2{0.f, 1.f} } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, InputTypeKeyBoard::IsPressed, dae::MoveCommand{ Qbert2.get(), glm::vec2{1.f, 0.f} } );
	scene.Add( Qbert2 );

	//SOUNDS
	//std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::_ss_instance{ std::make_unique<dae::NullSoundSystem>() };
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}