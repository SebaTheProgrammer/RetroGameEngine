#pragma once
#include <cstdint>

namespace dae
{
	enum EventType
	{
		LEVEL_STARTED,
		PLAYER_SPAWNED,
		PLAYER_DIED,
		PLAYER_HIT,
		PLAYER_WON,
		PLAYER_LOST,
		LEVEL_RESTART,
		KILL_ENEMY,
		PLAYER_MOVED,
		PLAYER_OUT_OF_BOUNDS
	};
}

