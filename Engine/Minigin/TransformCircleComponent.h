#pragma once
#include "BaseComponent.h"
namespace dae
{
	class BaseComponent;

	class TransformCircleComponent : public BaseComponent
	{
		public:
			TransformCircleComponent( GameObject* const parentGameObject, float radius, float rotationSpeed = 1.f );

			virtual ~TransformCircleComponent() = default;
			TransformCircleComponent( const TransformCircleComponent& other ) = delete;
			TransformCircleComponent( TransformCircleComponent&& other ) = delete;
			TransformCircleComponent& operator=( const TransformCircleComponent& other ) = delete;
			TransformCircleComponent& operator=( TransformCircleComponent&& other ) = delete;

			virtual void Update() override;

	private:

		const float m_Radius{};

		float m_CurrentAngle{}; // in radians
		float m_RotationSpeed{}; // radians per second
	};
}

