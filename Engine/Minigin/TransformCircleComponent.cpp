#include "TransformCircleComponent.h"
#include "GameTime.h"
#include <iostream>

constexpr float PI_F = 3.14159265f;

dae::TransformCircleComponent::TransformCircleComponent( GameObject* const parentGameObject, float radius, float rotationSpeed )
	: BaseComponent( parentGameObject )
	, m_Radius{ radius }
	, m_RotationSpeed{ rotationSpeed }
{
}

void dae::TransformCircleComponent::Update()
{
	m_CurrentAngle += GameTime::GetInstance().GetDeltaTime() * m_RotationSpeed;
	while ( m_CurrentAngle >= 2 * PI_F ) m_CurrentAngle -= 2 * PI_F;


	float xPos{ cosf( m_CurrentAngle ) * m_Radius };
	float yPos{ sinf( m_CurrentAngle ) * m_Radius };

	GetOwner()->SetLocalTransform( xPos, yPos, 0.f );

}
