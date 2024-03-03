#include "TransformCircleComponent.h"
#include "GameTime.h"
#include <iostream>

void dae::TransformCircleComponent::Update()
{
	const float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
	const auto pos = m_pGameObject->GetLocalTransform().GetPosition();

	m_X = pos.x + cosf( m_Angle ) * m_Radius;
	m_Y = pos.y + sinf( m_Angle ) * m_Radius;
	if ( m_Clockwise )
	{
		m_Angle += m_Speed * deltaTime;
	}
	else
	{
		m_Angle -= m_Speed * deltaTime;
	}

	m_pGameObject->SetLocalPosition( m_X, m_Y, 0);
}

void dae::TransformCircleComponent::Render() const
{
	
}

void dae::TransformCircleComponent::SetRadius( float radius )
{
	m_Radius = radius;
}

void dae::TransformCircleComponent::SetSpeed( float speed )
{
	m_Speed = speed;
}

void dae::TransformCircleComponent::SetAngle( float angle )
{
	m_Angle = angle;
}

void dae::TransformCircleComponent::SetDirection( bool clockwise )
{
	m_Clockwise = clockwise;
}
