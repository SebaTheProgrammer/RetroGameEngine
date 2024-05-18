#include "QBert.h"
#include "ResourceManager.h"
#include "PyramidCubes.h"
#include "PlayerCommands.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureIdleBack, bool keyboardinput )
	:BaseComponent( parentGameObject )
	, m_KeyBoardInput( keyboardinput )
	, m_X( 0 )
	, m_Y( 0 )

{
	m_pTextureIdle = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdle, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureIdleBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleBack, m_Scale, 1, 8, 0, m_FrameTime );

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
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, -1.2f}, SingleMovementComponent::Direction::RightUp } );

		dae::InputManager::GetInstance().BindActionGamePad( XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsPressed,
			SingleMoveCommand{ GetOwner(), glm::vec2{0.75f, 1.2f}, SingleMovementComponent::Direction::RightDown } );
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
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Update();
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
	case AnimationState::IdleBack:
		m_pTextureIdleBack->Render();
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
	m_pTextureIdleBack->Mirror( mirror );
}

void QBert::ResetPosition()
{
	m_CanMove = true;
	m_pSingleMovenment->SetCanMove( true );
	SetAnimationState( AnimationState::Idle );
	GetOwner()->SetLocalTransform( { 300, 90 } );
}

void QBert::GameOver()
{
	m_CanMove = false;
	m_pSingleMovenment->SetCanMove( false );
}
