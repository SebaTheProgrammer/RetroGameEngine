#pragma once
#include "BaseComponent.h"
#include "OnDeathEvent.h"
#include "OnTextChangedEvent.h"
namespace dae
{
	class OnDeathEvent;
	class OnTextChangedEvent;

	class HealthComponent : public BaseComponent
	{
		public:
		HealthComponent( GameObject* const parentGameObject, int health);
		virtual ~HealthComponent() = default;

		HealthComponent( const HealthComponent& other ) = delete;
		HealthComponent( HealthComponent&& other ) = delete;
		HealthComponent& operator=( const HealthComponent& other ) = delete;
		HealthComponent& operator=( HealthComponent&& other ) = delete;

		void TakeDamage( int damage );
		void Heal( int heal );

		int GetHealth() const { return m_Health; }

		//void SetOnDeathEvent( OnDeathEvent event ) { m_DeathEvent = event; }
		//OnDeathEvent GetOnDeathEvent() { m_DeathEvent; }
		
		//void SetText( const std::string& text ) { m_DeathEvent = text; }

		private:

		int m_Health;
		//OnDeathEvent m_DeathEvent;
		//OnTextChangedEvent m_OnTextChangedEvent;
	};
}

