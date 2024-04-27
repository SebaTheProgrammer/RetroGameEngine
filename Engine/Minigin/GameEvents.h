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
		LEVEL_ENDED,
		KILL_ENEMY,
	};

	/*class GameEvents
	{
	public:
			struct Event {
				static const uint8_t MAX_ARGS = 8;

				EventType m_type;
				uint8_t m_numArgs;
			};

			template<typename... Args>
			using Callback = void ( * )( const Event&, Args... );

			template<typename... Args>
			void Invoke( Args&&... args ) {
				for ( auto& listener : m_listeners ) {
					listener->OnEvent( m_event, std::forward<Args>( args )... );
				}
			}

			template<typename... Args>
			void AddCallback(Callback<Args...> callback ) {
				m_listeners.push_back( callback );
			}

		private:
		Event m_event;
		std::vector<void*> m_listeners;
		};

		class IGameEventListener
		{
			public:
			virtual void OnEvent( const GameEvents::Event& event ) = 0;
		};
	}*/
}

