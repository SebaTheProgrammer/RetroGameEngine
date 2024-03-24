#pragma once
#include "Observer.h"
#include "GameEvents.h"
#include "GameActor.h"

namespace dae
{
	class GameActor;
	class GameEvents;
	class Achievement : public Observer
	{
	public:
		enum struct Achievements
		{
			LEVEL_STARTED,
			LEVEL_ENDED,
			PLAYER_DIED,
			// etc...
		};

		void Notify( GameEvents::EventType event, GameActor* actor ) override
		{
			switch ( event )
			{
			case GameEvents::LEVEL_STARTED:
				Unlock( Achievement::Achievements::LEVEL_STARTED );
				break;
			case GameEvents::LEVEL_ENDED:
				Unlock( Achievement::Achievements::LEVEL_ENDED );
				break;
			case GameEvents::PLAYER_DIED:
				Unlock( Achievement::Achievements::PLAYER_DIED );
				break;
			}
		}
	private:
		void Unlock( Achievement::Achievements achievement )
		{
			// code to unlock an achievement...
		}
	};
}