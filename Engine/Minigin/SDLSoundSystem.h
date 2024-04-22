#pragma once
#include "SoundSystem.h"
//#include <SDL_mixer.h>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		void PlaySound( const sound_id id, const float volume = 100 ) override
		{
			/*auto audioclip = audioclips[ id ];
			if ( !audioclip->is_loaded() )
				audioclip->load();

			audioclip->set_volume( volume );

			audioclip->play();*/
		}
	};
}