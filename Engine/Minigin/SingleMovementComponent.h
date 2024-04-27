#pragma once
#include "MovenmentComponent.h"

namespace dae
{
	class SingleMovementComponent final : public MovenmentComponent
	{
	public:

		SingleMovementComponent( GameObject* const parentGameObject,float speed, float timeTakenForStep );
		virtual ~SingleMovementComponent() = default;
		SingleMovementComponent( const SingleMovementComponent& other ) = delete;
		SingleMovementComponent( SingleMovementComponent&& other ) = delete;
		SingleMovementComponent& operator=( const SingleMovementComponent& other ) = delete;
		SingleMovementComponent& operator=( SingleMovementComponent&& other ) = delete;

		void SingleMove( glm::vec2 direction );

		bool IsMovementInProgress() const { return m_MovementInProgress; }

		private:
			float m_Speed;
			bool m_MovementInProgress{ false };
			float m_StepSize{ 1.2f };
			float m_MovementDelayTimer{ -1 };
			float m_ElapsedTime{ 0.0f };

			const float m_TimeBetweenSteps{ 0.5f };
	};
}

