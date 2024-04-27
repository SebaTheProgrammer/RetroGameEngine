#pragma once
#include <vector>
#include "Observer.h"
#include "GameEvents.h"

namespace dae
{
	class Observer;
	class GameEvents;

	class GameActor
	{
	public:

		virtual ~GameActor() = default;

		void AddObserver( Observer* observer ) 
		{
			m_observers.emplace_back( observer );
		}
		void RemoveObserver( Observer* observer )
		{
			m_observers.erase( std::remove( m_observers.begin(), m_observers.end(), observer ), m_observers.end() );
		}

	protected:
		GameActor() = default;

		void NotifyObservers( EventType event, GameObject* gameObj )
		{
			for ( const auto& observer : m_observers )
			{
				observer->Notify(event, gameObj );
			}
		}
	private:
		std::vector<Observer*> m_observers;
	};
}


