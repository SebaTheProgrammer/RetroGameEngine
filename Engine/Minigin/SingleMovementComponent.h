#pragma once
#include "MovenmentComponent.h"

class SingleMovementComponent final : public dae::MovenmentComponent
{
public:
	enum class Direction
	{
		LeftUp,
		RightDown,
		LeftDown,
		RightUp
	};

	SingleMovementComponent( dae::GameObject* const parentGameObject, float speed, float timeTakenForStep, bool instantJump );
	virtual ~SingleMovementComponent() = default;
	SingleMovementComponent( const SingleMovementComponent& other ) = delete;
	SingleMovementComponent( SingleMovementComponent&& other ) = delete;
	SingleMovementComponent& operator=( const SingleMovementComponent& other ) = delete;
	SingleMovementComponent& operator=( SingleMovementComponent&& other ) = delete;

	void SingleMove( glm::vec2 direction, Direction dir, bool byPC );
	void SetCanMove( bool canMove ) { m_CanMove = canMove; }
	void SetInstantJump( bool instantJump ) { m_InstantJump = instantJump; }
	void SetHasControl( bool hasControl ) { m_HasControl = hasControl; }

	bool GetCanMove(){return m_CanMove;}

	bool IsMovementInProgress() const { return m_MovementInProgress; }

	Direction GetDirection() const { return m_Direction; }

private:
	Direction m_Direction{ Direction::LeftDown };
	float m_Speed;
	bool m_MovementInProgress{ false };
	bool m_CanMove{ false };
	float m_StepSize{ 1.2f };
	float m_MovementDelayTimer{ -1 };
	float m_ElapsedTime{ 0.0f };
	bool m_InstantJump;
	bool m_HasControl{ true };

	const float m_TimeBetweenSteps{ 0.5f };
};

