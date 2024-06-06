#include "ChangeNameScreen.h"
#include "Commands.h"
#include <ButtonManagerComponent.h>

ChangeNameScreen::ChangeNameScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font )
	: BaseComponent( parentGameObject )
{
	//m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	//std::shared_ptr<dae::Command> myCommand = std::make_shared< SinglePlayer>( m_Buttons[ m_Buttons.size() - 1].get());
	//auto button = std::make_shared<dae::ButtonComponent>( m_Buttons[ m_Buttons.size() - 1 ].get(), "Solo", font, myCommand );
	//m_Buttons[ m_Buttons.size() - 1 ]->SetLocalTransform( { 275, 200 } );
	//m_Buttons[ m_Buttons.size() - 1 ]->AddComponent( button );

	//m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	////std::shared_ptr<dae::Command> myCommand = std::make_shared< SinglePlayer>( m_Buttons[ m_Buttons.size() - 1 ].get() );
	//auto button2 = std::make_shared<dae::ButtonComponent>( m_Buttons[ m_Buttons.size() - 1 ].get(), "Solo", font, myCommand );
	//m_Buttons[ m_Buttons.size() - 1 ]->SetLocalTransform( { 275, 200 } );
	//m_Buttons[ m_Buttons.size() - 1 ]->AddComponent( button );

	//m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	////std::shared_ptr<dae::Command> myCommand = std::make_shared< SinglePlayer>( m_Buttons[ m_Buttons.size() - 1 ].get() );
	//auto button3 = std::make_shared<dae::ButtonComponent>( m_Buttons[ m_Buttons.size() - 1 ].get(), "Solo", font, myCommand );
	//m_Buttons[ m_Buttons.size() - 1 ]->SetLocalTransform( { 275, 200 } );
	//m_Buttons[ m_Buttons.size() - 1 ]->AddComponent( button );

	//std::vector<std::shared_ptr<dae::ButtonComponent>> allButtons = { button,button2,button3 };
	//auto buttonManager = std::make_shared<dae::ButtonManagerComponent>( m_ButtonsHandeler.get(), texture, allButtons );
	//m_ButtonsHandeler->AddComponent( buttonManager );

	//dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsDownThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get() } );
	//dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsDownThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get() } );
	//dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_SPACE, InputTypeKeyBoard::IsDownThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );

	//dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get() } );
	//dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get() } );
	//dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
}

void ChangeNameScreen::Update()
{
	//for ( auto button : m_Buttons )
	//{
	//	button->Update();
	//}

	//m_ButtonsHandeler->Update();
}

void ChangeNameScreen::Render() const
{
	//for ( auto button : m_Buttons )
	//{
	//	button->Render();
	//}

	//m_ButtonsHandeler->Render();
}
