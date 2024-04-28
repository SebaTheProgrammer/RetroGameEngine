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
	QBert( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureIdle, std::shared_ptr<dae::Texture2D> textureJump,
		std::shared_ptr<dae::Texture2D> textureIdleBack, std::shared_ptr<dae::Texture2D> textureJumpBack,
		bool keyboardinput);
	virtual ~QBert() = default;

	void Update() override;
	void Render() const override;

	void GetsHit();

	int GetIndex() const { return m_Index; }

	enum class AnimationState
	{
		Idle,
		Jump,
		IdleBack,
		JumpBack
	};

	void SetAnimationState( AnimationState state ) { m_CurrentState = state; }

private:
	bool m_KeyBoardInput;

	//all the textures, how can we make this more efficient?
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdle;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJump;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleBack;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJumpBack;

	std::shared_ptr<dae::MovenmentComponent> m_pMovenment;
	std::shared_ptr<dae::SingleMovementComponent> m_pSingleMovenment;

	//Stats
	std::shared_ptr<LevelHandeler> m_pStats;
	std::shared_ptr < dae::TextComponent> m_pHealthDisplay;
	//hitbox
	//lives
	//ect

	float m_X;
	float m_Y;

	const float m_Scale = 1.2f;
	const float m_FrameTime = 0.3f;
	const float m_Speed = 47.f;

	AnimationState m_CurrentState = AnimationState::Idle;

	int m_Index{ 0 };
};