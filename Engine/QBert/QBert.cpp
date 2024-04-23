#include "QBert.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, bool keyboardinput )
	:BaseComponent( parentGameObject )
	, m_KeyBoardInput( keyboardinput )
	, m_X( 0 )
	, m_Y( 0 )

{
	m_pTexture = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, texture, 1, 1, 1, 0, 0.0f );
	GetOwner()->AddComponent( m_pTexture );


	//REMAKE THE MOVEMENT
	if ( m_KeyBoardInput ) 
	{
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, dae::MoveCommand{ this->GetOwner(), glm::vec2{0.f, -1.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, dae::MoveCommand{ this->GetOwner(), glm::vec2{-1.f, 0.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, dae::MoveCommand{ this->GetOwner(), glm::vec2{0.f, 1.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, dae::MoveCommand{ this->GetOwner(), glm::vec2{1.f, 0.f} } );
	}
	else 
	{
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed, dae::MoveCommand{ this->GetOwner(), glm::vec2{0.f, -1.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed, dae::MoveCommand{ this->GetOwner(), glm::vec2{-1.f, 0.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed, dae::MoveCommand{ this->GetOwner(), glm::vec2{1.f, 0.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed, dae::MoveCommand{ this->GetOwner(), glm::vec2{0.f, 1.f} } );
	}
}

void QBert::Update()
{
		//m_pTexture->Update();
}

void QBert::Render() const
{
		//m_pTexture->Render();
}
