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

		Observer( const Observer& other ) = delete;
		Observer( Observer&& other ) noexcept = delete;
		Observer& operator=( const Observer& other ) = delete;
		Observer& operator=( Observer&& other ) noexcept = delete;

		virtual void Notify( GameEvents::EventType event, GameActor* actor ) = 0;

	protected:
		Observer() = default;

	};
}

