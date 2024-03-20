#pragma once

namespace dae
{
	class GameEvents
	{
		enum EventType {
			LEVEL_STARTED,
			PLAYER_SPAWNED,
			PLAYER_DIED,
			PLAYER_HIT,
			PLAYER_WON,
			PLAYER_LOST,
			LEVEL_ENDED,
		};

		struct Event {
			static const uint8_t MAX_ARGS = 8;

			EventType m_type;
			uint8_t m_numArgs;
		};

	};

}

