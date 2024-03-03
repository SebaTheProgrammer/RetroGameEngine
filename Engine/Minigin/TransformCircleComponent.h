#pragma once
#include "BaseComponent.h"
namespace dae
{
	class BaseComponent;

	class TransformCircleComponent : public BaseComponent
	{
		public:
		TransformCircleComponent() = default;
		virtual ~TransformCircleComponent() = default;

		TransformCircleComponent(const TransformCircleComponent& other) = delete;
		TransformCircleComponent(TransformCircleComponent&& other) = delete;
		TransformCircleComponent& operator=(const TransformCircleComponent& other) = delete;
		TransformCircleComponent& operator=(TransformCircleComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void SetRadius(float radius);
		virtual void SetSpeed(float speed);
		virtual void SetAngle(float angle);
		virtual void SetDirection(bool clockwise);
		private:
			float m_Radius;
			float m_X;
			float m_Y;
			float m_Angle;
			float m_Speed;
			bool m_Clockwise;
	};
}

