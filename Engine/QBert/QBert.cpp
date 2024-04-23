#include "QBert.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureJump,
	std::shared_ptr<dae::Texture2D> textureIdleBack, std::shared_ptr<dae::Texture2D> textureJumpBack, bool keyboardinput )
	:BaseComponent( parentGameObject )
	, m_KeyBoardInput( keyboardinput )
	, m_X( 0 )
	, m_Y( 0 )

{
	m_pTextureIdle = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdle, m_Scale, 1, 8, 0, m_FrameTime );
	GetOwner()->AddComponent( m_pTextureIdle );
	m_pTextureJump = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJump, m_Scale, 1, 8, 0, m_FrameTime );
	GetOwner()->AddComponent( m_pTextureJump );
	m_pTextureIdleBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleBack, m_Scale, 1, 8, 0, m_FrameTime );
	GetOwner()->AddComponent( m_pTextureIdleBack );
	m_pTextureJumpBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJumpBack, m_Scale, 1, 6, 0, m_FrameTime );
	GetOwner()->AddComponent( m_pTextureJumpBack );

	m_pMovenment = std::make_shared<dae::MovenmentComponent>( parentGameObject, m_Speed );
	GetOwner()->AddComponent( m_pMovenment );

	m_pSingleMovenment = std::make_shared<dae::SingleMovementComponent>( parentGameObject, m_Speed, 1.f );
	GetOwner()->AddComponent( m_pSingleMovenment );

	//REMAKE THE MOVEMENT FOR PRESSES
	if ( m_KeyBoardInput )
	{
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, dae::SingleMoveCommand{ GetOwner(), glm::vec2{-1.f, -1.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, dae::SingleMoveCommand{ GetOwner(), glm::vec2{-1.f, 1.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, dae::SingleMoveCommand{ GetOwner(), glm::vec2{1.f, 1.f} } );
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, dae::SingleMoveCommand{ GetOwner(), glm::vec2{1.f, -1.f} } );
	}
	else
	{
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{0.f, -1.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{-1.f, 0.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{1.f, 0.f} } );
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed, dae::MoveCommand{ GetOwner(), glm::vec2{0.f, 1.f} } );
	}

	m_pTextureIdle->Mirror( true );
}

void QBert::Update()
{
	switch ( m_CurrentState ) 
	{
	case AnimationState::Idle:
		m_pTextureIdle->Update();
		break;
	case AnimationState::Jump:
		m_pTextureJump->Update();
		break;
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Update();
		break;
	case AnimationState::JumpBack:
		m_pTextureJumpBack->Update();
		break;
	}
}

void QBert::Render() const
{
	switch ( m_CurrentState ) 
	{
	case AnimationState::Idle:
		m_pTextureIdle->Render();
		break;
	case AnimationState::Jump:
		m_pTextureJump->Render();
		break;
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Render();
		break;
	case AnimationState::JumpBack:
		m_pTextureJumpBack->Render();
		break;
	}
}
