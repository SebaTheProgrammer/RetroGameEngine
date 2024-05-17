#pragma once
#include "BaseComponent.h"
#include "GameActor.h"
#include <AnimatedTextureComponent.h>

class Coily : public dae::BaseComponent, public dae::GameActor
{
public:
	Coily( dae::GameObject* parentGameObject, 
		std::shared_ptr<dae::Texture2D> textureIdleEgg, std::shared_ptr<dae::Texture2D> textureJumpEgg, 
		std::shared_ptr<dae::Texture2D> textureIdleSnake,std::shared_ptr<dae::Texture2D> textureJumpSnake);
	~Coily() = default;
	Coily( const Coily& other ) = delete;
	Coily( Coily&& other ) = delete;
	Coily& operator=( const Coily& other ) = delete;
	Coily& operator=( Coily&& other ) = delete;

	enum class AnimationState
	{
		IdleSnake,
		IdleBackSnake,
		Egg,
	};

	void Update() override;
	void Render() const override;

	void SetAnimationState( AnimationState state );

	void SetPyramidPosition( const int x, const int y );
	int GetRow() const { return m_Row; }
	int GetCol() const { return m_Col; }

private:
	const float m_FrameTime = 0.3f;

	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleEgg;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJumpEgg;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleSnake;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJumpSnake;

	AnimationState m_CurrentState = AnimationState::Egg;

	int m_Row;
	int m_Col;
};

