#include "QBert.h"
#include "ResourceManager.h"
#include "PyramidCubes.h"
#include "PlayerCommands.h"
#include <GameTime.h>
#include "TextureComponent.h"
#include <iostream>
#include <ServiceLocator.h>
#include "InputBindsManager.h"
#include "MovementManager.h"

QBert::QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureIdleBack )
	:BaseComponent( parentGameObject )
	, m_X( 0 )
	, m_Y( 0 )

{
	m_pTextureIdle = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdle, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureIdleBack = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleBack, m_Scale, 1, 8, 0, m_FrameTime );
	m_pTextureHit = std::make_shared<dae::TextureComponent>( parentGameObject, "Qbert Curses.png" );

	m_pMovenment = std::make_shared<dae::MovenmentComponent>( parentGameObject, m_Speed );
	GetOwner()->AddComponent( m_pMovenment );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, false );
	m_pSingleMovenment->SetHasControl( true );
	GetOwner()->AddComponent( m_pSingleMovenment );

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

	if ( m_GetsHit )
	{
		m_pTextureHit->Update();

		m_HitTimer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_HitTimer >= m_HitWaitTime ) 
		{
			m_HitTimer = 0;
			m_pSingleMovenment->SetCanMove( true );
			m_GetsHit= false;
		}
	}

	if ( m_Floating ) 
	{
		glm::vec2 currentPosition = GetOwner()->GetLocalTransform().GetPosition();

		glm::vec2 direction = glm::vec2{ 300, 50 } - currentPosition;
		float distance = glm::length( direction );

		if ( distance > 0.0f )
		{
			direction /= distance;

			float moveDistance = m_Speed * dae::GameTime::GetInstance().GetDeltaTime();

			glm::vec2 newPosition;
			if ( moveDistance < distance ) 
			{
				newPosition = currentPosition + direction * moveDistance;
			}
			else 
			{
				newPosition = glm::vec2{ 300, 90 };
				m_Floating = false;
			}

			GetOwner()->SetLocalTransform( newPosition );
		}
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

	if ( m_GetsHit ) 
	{
		m_pTextureHit->Render();
	}
}

void QBert::GetsHit()
{
	m_GetsHit = true;
	m_pSingleMovenment->SetCanMove( false );
	if ( m_WichPlayer == 1 ) 
	{
		NotifyObservers( dae::EventType::PLAYER1_HIT, GetOwner() );
	}
	else
	{
		NotifyObservers( dae::EventType::PLAYER2_HIT, GetOwner() );
	}
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

void QBert::FloatToTop()
{
	m_Floating = true;
}

void QBert::ResetPosition()
{
	m_GetsHit = true;
	m_pSingleMovenment->SetCanMove( true );
	SetAnimationState( AnimationState::Idle );
	GetOwner()->SetLocalTransform( { 300, 90 } );
}

void QBert::ResetQBert()
{
	m_Floating = false;
	ResetPosition();
	m_GetsHit = false;
	m_HitTimer = 0;
}

void QBert::GameOver()
{
	m_pSingleMovenment->SetCanMove( false );
}

void QBert::SetLeftBottom( int levelsize )
{
	glm::vec2 totalDistance{};
	for ( int index = 0; index < levelsize - 1; ++index ) {
		totalDistance += glm::vec2{ -0.75f, 1.2f } * 30.f;
	}
	GetOwner()->SetLocalTransform( { 300 + totalDistance.x, 85 + totalDistance.y } );
}

void QBert::SetRightBottom( int levelsize )
{
	glm::vec2 totalDistance{};
	for ( int index = 0; index < levelsize - 1; ++index ) {
		totalDistance += glm::vec2{ 0.75f, 1.2f } * 30.f;
	}
	GetOwner()->SetLocalTransform( { 300 + totalDistance.x, 85 + totalDistance.y } );
}

void QBert::SetInputKeyBoard()
{
	auto movement = MovementManager::GetInstance();
	dae::InputManager::GetInstance().BindActionKeyBoard(
		InputBindsManager::GetInstance().GetKeyboardGameUp(),
		InputTypeKeyBoard::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Leftup.vector, movement.Leftup.direction }
	);

	dae::InputManager::GetInstance().BindActionKeyBoard(
		InputBindsManager::GetInstance().GetKeyboardGameLeft(),
		InputTypeKeyBoard::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Leftdown.vector, movement.Leftdown.direction }
	);

	dae::InputManager::GetInstance().BindActionKeyBoard(
		InputBindsManager::GetInstance().GetKeyboardGameDown(),
		InputTypeKeyBoard::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Rightdown.vector, movement.Rightdown.direction }
	);

	dae::InputManager::GetInstance().BindActionKeyBoard(
		InputBindsManager::GetInstance().GetKeyboardGameRight(),
		InputTypeKeyBoard::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Rightup.vector, movement.Rightup.direction }
	);

}

void QBert::SetInputController(int index)
{
	auto movement = MovementManager::GetInstance();
	auto& inputManager = dae::InputManager::GetInstance();
	auto& inputBindsManager = InputBindsManager::GetInstance();

	inputManager.BindActionGamePad(
		index,
		inputBindsManager.GetControllerGameUp(),
		InputTypeGamePad::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Leftup.vector, movement.Leftup.direction }
	);

	inputManager.BindActionGamePad(
		index,
		inputBindsManager.GetControllerGameLeft(),
		InputTypeGamePad::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Leftdown.vector, movement.Leftdown.direction }
	);

	inputManager.BindActionGamePad(
		index,
		inputBindsManager.GetControllerGameRight(),
		InputTypeGamePad::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Rightup.vector, movement.Rightup.direction }
	);

	inputManager.BindActionGamePad(
		index,
		inputBindsManager.GetControllerGameDown(),
		InputTypeGamePad::IsPressed,
		SingleMoveCommand{ GetOwner(), movement.Rightdown.vector, movement.Rightdown.direction }
	);
}
