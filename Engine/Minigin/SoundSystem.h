#pragma once
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include <iostream>
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual unsigned short AddSound( const std::string& name, const std::string& path ) = 0;
		virtual void Play( unsigned short id, int volume ) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Mute() = 0;
		virtual void Unmute() = 0;

		virtual void SetVolume( float volume ) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		virtual ~NullSoundSystem() = default;
		virtual void Play( unsigned short id, int volume ) override 
		{
			std::cout << "NullSoundSystem::Play::"<< id<<""<<volume<<std::endl;
		};
		virtual void Pause() override
		{
			std::cout << "NullSoundSystem::Pause\n";
		};
		virtual void Resume() override
		{
			std::cout << "NullSoundSystem::Resume\n";
		};
		virtual void Mute() override
		{
			std::cout << "NullSoundSystem::Mute\n";
		};
		virtual void Unmute() override
		{
			std::cout << "NullSoundSystem::Unmute\n";
		};
		virtual void SetVolume( float volume ) override
		{
			std::cout << "NullSoundSystem::SetVolume::" << volume << "\n";
		};
		virtual unsigned short AddSound( const std::string& name, const std::string& path ) override
		{
			std::cout << "NullSoundSystem::AddSound::" << name << " " << path << "\n";
			return 0;
		}
	};

	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		LoggingSoundSystem( std::unique_ptr<SoundSystem>&& soundSystem ) :m_SoundSystem( std::move( soundSystem ) ) {};
		virtual ~LoggingSoundSystem() = default;

		virtual unsigned short AddSound( const std::string& name, const std::string& path ) override 
		{
			std::cout << "Added sound " << name << " at volume " << path << "\n";
			return m_SoundSystem->AddSound( name, path );
		}

		virtual void Play( unsigned short id, int volume ) override 
		{
			m_SoundSystem->Play( id, volume );
			std::cout << "playing " << id << " at volume " << volume << "\n";
		}
		virtual void Pause() override 
		{
			m_SoundSystem->Pause(); std::cout << "Sound paused \n";
		}
		virtual void Resume() override 
		{
			m_SoundSystem->Resume(); std::cout << "Sound Resumed \n";
		}
		virtual void Mute() override 
		{
			m_SoundSystem->Mute(); std::cout << "Sound muted \n";
		}
		virtual void Unmute() override 
		{
			m_SoundSystem->Mute(); std::cout << "Sound unmuted \n";
		}

		virtual void SetVolume( float volume ) override 
		{
			std::cout << "Set volume to: " << volume << "\n";
			m_SoundSystem->SetVolume( volume ); 
		}

	private:
		std::unique_ptr<SoundSystem> m_SoundSystem;

	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

		SDLSoundSystem( const SDLSoundSystem& other ) = delete;
		SDLSoundSystem( SDLSoundSystem&& other ) = delete;
		SDLSoundSystem& operator=( const SDLSoundSystem& other ) = delete;
		SDLSoundSystem& operator=( SDLSoundSystem&& other ) = delete;

		virtual unsigned short AddSound( const std::string& name, const std::string& path ) override;

		virtual void Play( unsigned short id, int volume ) override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void Mute() override;
		virtual void Unmute() override;

		virtual void SetVolume( float volume ) override;

	private:
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> m_pImplSoundSystem;

	};
}
