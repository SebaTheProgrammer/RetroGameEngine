#include "HealthComponent.h"

dae::HealthComponent::HealthComponent( GameObject* const parentGameObject, int health) : 
	BaseComponent( parentGameObject )
, m_Health( health )
{
}

void dae::HealthComponent::TakeDamage( int damage )
{
	m_Health -= damage;
	if(m_Health <= 0 )
	{
		m_Health = 0;
	} 
}

void dae::HealthComponent::Heal( int heal )
{
	m_Health += heal;
}
