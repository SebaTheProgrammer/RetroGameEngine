#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
    class SoundSystem;
    class NullSoundSystem;

	class ServiceLocator final
	{
	public:
		~ServiceLocator();

		ServiceLocator( const ServiceLocator& other ) = delete;
		ServiceLocator( ServiceLocator&& other ) noexcept = delete;
		ServiceLocator& operator=( const ServiceLocator& other ) = delete;
		ServiceLocator& operator=( ServiceLocator&& other ) noexcept = delete;

		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem( std::unique_ptr<SoundSystem> ss );

		static void CleanUp();

	private:
		ServiceLocator() = default;

		static std::unique_ptr<SoundSystem> s_SoundSystemInstance;

	};
}