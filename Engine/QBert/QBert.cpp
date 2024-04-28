#include "QBert.h"
#include "ResourceManager.h"
#include "PyramidCubes.h"
#include "PlayerCommands.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureJump,
	std::shared_ptr<dae::Texture2D> textureIdleBack, std::shared_ptr<dae::Texture2D> textureJumpBack, bool keyboardinput )
	:BaseComponent( parentGameObject )
	, m_KeyBoardInput( keyboardinput )
	, m_X( 0 )
	, m_Y( 0 )

{
	//all the textures, how can we make this more efficient?
	m_pTextureIdle = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdle, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureJump = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJump, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureIdleBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleBack, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureJumpBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJumpBack, m_Scale, 1, 6, 0, m_FrameTime );

	//movement
	m_pMovenment = std::make_shared<dae::MovenmentComponent>( parentGameObject, m_Speed );
	GetOwner()->AddComponent( m_pMovenment );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps );
	GetOwner()->AddComponent( m_pSingleMovenment );

	if ( m_KeyBoardInput )
	{
		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsPressed, 
			SingleMoveCommand{ GetOwner(), glm::vec2{-0.75f, -1.2f}, SingleMovementComponent::Direction::LeftUp } );

		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, InputTypeKeyBoard::IsPressed, 
			SingleMoveCommand{ GetOwner(), glm::vec2{-0.75f, 1.2f}, SingleMovementComponent::Direction::LeftDown } );

		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsPressed, 
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, 1.2f}, SingleMovementComponent::Direction::RightDown } );

		dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, InputTypeKeyBoard::IsPressed, 
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, -1.2f}, SingleMovementComponent::Direction::RightUp } );
	}
	else
	{
		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsPressed,
			SingleMoveCommand{ GetOwner(),  glm::vec2{-0.75f, -1.2f}, SingleMovementComponent::Direction::LeftUp } );

		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsPressed,
			SingleMoveCommand{ GetOwner(), glm::vec2{-0.75f, 1.2f}, SingleMovementComponent::Direction::LeftDown } );

		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsPressed,
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, 1.2f}, SingleMovementComponent::Direction::RightDown } );

		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed,
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, -1.2f}, SingleMovementComponent::Direction::RightUp } );
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

void QBert::GetsHit()
{
	NotifyObservers( dae::EventType::PLAYER_HIT, GetOwner() );
}

void QBert::Moved( SingleMovementComponent::Direction dir )
{
	switch ( dir )
	{
	case SingleMovementComponent::Direction::LeftUp:
		SetAnimationState( AnimationState::IdleBack );
		SetMirror( true );
		break;
	case SingleMovementComponent::Direction::RightDown:
		SetAnimationState( AnimationState::Idle );
		SetMirror( false );
		break;
	case SingleMovementComponent::Direction::LeftDown:
		SetAnimationState( AnimationState::Idle );
		SetMirror( true );
		break;
	case SingleMovementComponent::Direction::RightUp:
		SetAnimationState( AnimationState::IdleBack );
		SetMirror( false );
		break;
	}

	NotifyObservers( dae::EventType::PLAYER_MOVED, GetOwner() );
}

void QBert::SetAnimationState( AnimationState state )
{
	m_CurrentState = state;
}

void QBert::SetMirror( bool mirror )
{
	m_pTextureIdle->Mirror( mirror );
	m_pTextureJump->Mirror( mirror );
	m_pTextureIdleBack->Mirror( mirror );
	m_pTextureJumpBack->Mirror( mirror );
}
