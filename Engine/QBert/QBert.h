#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include <AnimatedTextureComponent.h>
#include <MovenmentComponent.h>
#include <SingleMovementComponent.h>
#include "GameActor.h"
#include "LevelHandeler.h"
#include <TextComponent.h>

class QBert : public dae::BaseComponent, public dae::GameActor
{
	public:
	QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureIdleBack,
		bool keyboardinput);
	virtual ~QBert() = default;

	void Update() override;
	void Render() const override;

	void GetsHit();

	void Moved( SingleMovementComponent::Direction dir );

	SingleMovementComponent::Direction GetDirection() const { return m_pSingleMovenment->GetDirection(); }

	enum class AnimationState
	{
		Idle,
		IdleBack,
	};

	void SetAnimationState( AnimationState state );
	void SetMirror( bool mirror );
	bool CanMove() const { return m_CanMove; }
	void SetCanMove( bool canMove ) { m_CanMove = canMove; m_pSingleMovenment->SetCanMove( canMove ); };

	void ResetPosition();

	void GameOver();

	int GetHealth() const { return m_pStats->GetLives(); }
	void SetHealth( int health ) { m_pStats->SetLives( health ); }

private:
	bool m_KeyBoardInput;

	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdle;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleBack;

	std::shared_ptr<dae::MovenmentComponent> m_pMovenment;
	std::shared_ptr<SingleMovementComponent> m_pSingleMovenment;

	//Stats
	std::shared_ptr<LevelHandeler> m_pStats;
	std::shared_ptr < dae::TextComponent> m_pHealthDisplay;

	float m_X;
	float m_Y;

	const float m_Scale = 1.2f;
	const float m_FrameTime = 0.3f;
	const float m_Speed = 47.f;
	const float m_SpeedBetweenSteps = 0.7f;

	AnimationState m_CurrentState = AnimationState::Idle;

	bool m_CanMove = false;
};