#pragma once
#include "SoundSystem.h"
#include <SDL3/SDL_mixer.h>
#include <map>
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		void PlaySound( const sound_id id, const float volume = 100 ) override
		{
			/*	auto audioclip = audioclips[ id ];

				if ( !audioclip->is_loaded() )
					audioclip->load();

				audioclip->set_volume( volume );

				audioclip->play();
			}

			void PauseSound( const sound_id id ) override
			{
				auto audioclip = audioclips[ id ];

				if ( !audioclip->is_loaded() )
					audioclip->load();

				audioclip->pause();
			}

			void AddAudioClip( const sound_id id, const std::shared_ptr<AudioClip>& audioclip )
			{
				audioclips[ id ] = audioclip;
			}

			void RemoveAudioClip( const sound_id id )
			{
				audioclips.erase( id );
			}

			private:
				std::map<sound_id, std::shared_ptr<AudioClip>> audioclips{};*/
		}
	};
}