#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<dae::SoundSystem> _ss_instance;
	public:
		static dae::SoundSystem& GetSoundSystem() { return *_ss_instance; }
		static void RegisterSoundSystem( std::unique_ptr<dae::SoundSystem>&& ss ) { _ss_instance = std::move( ss ); }

		~ServiceLocator();
	};
}