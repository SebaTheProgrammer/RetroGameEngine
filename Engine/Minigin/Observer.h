#pragma once
#include <string>
#include "GameEvents.h"
#include "GameActor.h"

namespace dae
{
	class GameActor;
	class Observer
	{
		public:
		virtual ~Observer() = default;
		virtual void Notify( GameEvents event, dae::GameActor* gameobject ) = 0;
		virtual void Notify( GameEvents::EventType event, GameActor* actor ) = 0;
	};
}

