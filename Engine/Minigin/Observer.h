#pragma once
#include <string>
#include "GameEvents.h"
#include "GameActor.h"

namespace dae
{
	class Observer
	{
		public:
		virtual ~Observer() = default;
		virtual void Notify( GameEvents event, GameActor* gameobject ) = 0;
	};
}

