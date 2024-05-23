#pragma once
#include "BaseComponent.h"
#include "GameActor.h"
#include <AnimatedTextureComponent.h>
#include "SingleMovementComponent.h"

class Coily : public dae::BaseComponent, public dae::GameActor
{
public:
	Coily( dae::GameObject* parentGameObject, 
		std::shared_ptr<dae::Texture2D> textureCoily, int levelSize);
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
	void Jump( SingleMovementComponent::Direction dir );

	void SetAnimationState( AnimationState state );

	void SetPyramidPosition( const int x, const int y );
	int GetRow() const { return m_Row; }
	int GetCol() const { return m_Col; }

	void Mirror( bool mirror ) { m_pTextureCoily->Mirror( mirror ); }
	void Moved( SingleMovementComponent::Direction dir );
	void FollowPlayer( int playerRow, int playerCol );

private:
	int GetRowStartIndex(int col) const;
	int GetRowEndIndex(int col) const;

	const float m_FrameTime = 0.5f;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureCoily;

	AnimationState m_CurrentState = AnimationState::Egg;

	std::shared_ptr<SingleMovementComponent> m_pSingleMovenment;

	int m_LevelSize; //level size
	int m_Row{0};
	int m_Col{1};

	bool m_Started = false;
	const float m_StartTime = 6.f;
	const float m_JumpTime = 3.f;
	float m_Timer = 0.f;

	const float m_Speed = 47.f;
	const float m_SpeedBetweenSteps = 0.7f;
	SingleMovementComponent::Direction m_PrevDirection{};
};

