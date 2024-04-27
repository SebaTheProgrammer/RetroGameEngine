#pragma once
#include <string>
#include "GameEvents.h"

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

		virtual void Notify( EventType event, GameObject* gameObj ) = 0;

	protected:
		Observer() = default;

	};
}

