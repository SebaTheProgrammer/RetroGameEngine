#include "HealthComponent.h"

dae::HealthComponent::HealthComponent( GameObject* const parentGameObject, int health ) : BaseComponent( parentGameObject )
, m_Health( health )
{
}

void dae::HealthComponent::Update()
{
}

void dae::HealthComponent::TakeDamage( int damage )
{
	m_Health -= damage;
}

void dae::HealthComponent::Heal( int heal )
{
	m_Health += heal;
}
