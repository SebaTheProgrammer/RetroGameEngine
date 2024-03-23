#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	class Observer;

	class GameActor
	{
	public:
		void AddObserver( Observer* observer ) 
		{
			m_observers.push_back( observer );
		}
		void RemoveObserver( Observer* observer )
		{
			m_observers.erase( std::remove( m_observers.begin(), m_observers.end(), observer ), m_observers.end() );
		}
	protected:

	private:
		std::vector<Observer*> m_observers;
	};
}


