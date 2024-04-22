#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void PlaySound( const sound_id, const float ) override {}
	};

	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _ss_instance;

	public:
		static SoundSystem& get_sound_system() { return *_ss_instance; }
		static void register_sound_system( std::unique_ptr<SoundSystem>&& ss ) {
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move( ss );
		}
	};

}