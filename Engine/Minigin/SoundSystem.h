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
	using sound_id = unsigned short;

	struct soundinfo
	{
		sound_id id;
		float volume;
	};

	class SoundSystem
	{
	public:

		virtual ~SoundSystem() = default;
		virtual void AddSong( const sound_id id, const std::string& filePath ) = 0;
		virtual void Play( sound_id id, const float volume = 100 ) = 0;

		virtual int MaxVolume() const = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:

		virtual ~NullSoundSystem() = default;

		virtual void AddSong( const std::string&, sound_id ){};

		virtual void AddSoundEffect( const std::string&, sound_id ){};

		virtual void Play( sound_id, float ) override {};

		virtual int MaxVolume() const override { return 0; }
	};

	class LoggingSoundSystem final : public SoundSystem
	{
	public:

		explicit LoggingSoundSystem( std::unique_ptr<SoundSystem>&& soundSystem )
		{
			m_RealSS = std::move( soundSystem );
		}
		virtual ~LoggingSoundSystem() = default;

		virtual void AddSong( const std::string& filePath, sound_id id )
		{
			std::cout << "Adding song: " << filePath << " on id: " << id << ".\n";
			m_RealSS->AddSong( id, filePath );
		}

		void Play( sound_id id, float volume) override
		{
			m_RealSS->Play( id, volume);
			std::cout << "played with id: " << id << " volume: " << volume << "\n";
		}

		virtual int MaxVolume() const override
		{
			return m_RealSS->MaxVolume();
		}

	private:

		std::unique_ptr<SoundSystem> m_RealSS;

	};

	class SoundPlayer final
	{
	public:

		explicit SoundPlayer( const std::string& filePath ) { m_FilePath = filePath; };
		~SoundPlayer() { UnLoad(); };

		SoundPlayer( const SoundPlayer& other ) = delete;
		SoundPlayer( SoundPlayer&& other ) noexcept = delete;
		SoundPlayer& operator=( const SoundPlayer& other ) = delete;
		SoundPlayer& operator=( SoundPlayer&& other ) noexcept = delete;

		bool IsLoaded() const { return m_IsLoaded; };
		void Load(){ m_Music = Mix_LoadMUS( m_FilePath.c_str() ); m_IsLoaded = m_Music != nullptr; }
		void UnLoad(){ if ( m_IsLoaded ) { Mix_FreeMusic( m_Music ); m_Music = nullptr; m_IsLoaded = false; } }

		void SetVolume( int volume ){ Mix_VolumeMusic( volume ); }

		void Play(){ if ( m_IsLoaded ) { Mix_PlayMusic( m_Music, -1 ); } }
		void Pause(){ if ( m_IsLoaded ) { Mix_PauseMusic(); } }
		void Resume(){ if ( m_IsLoaded ) { Mix_ResumeMusic(); } }
		void Stop(){ if ( m_IsLoaded ) { Mix_HaltMusic(); } }

		static int MaxVolume(){ return MIX_MAX_VOLUME; }

	private:

		bool m_IsLoaded{ false };
		std::string m_FilePath;
		Mix_Music* m_Music{ nullptr };

	};

    class SDLSoundSystem final : public SoundSystem
    {
    public:
		SDLSoundSystem() { if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 4, 2048 ) < 0 ) { return; } };

		~SDLSoundSystem() override { Mix_CloseAudio(); };

        void Play( const sound_id id, const float volume = 100 ) override
        {
			std::unique_lock<std::mutex> lock( m_Mutex );

			m_Queue.push( soundinfo{ id, volume} );
			m_ConditionToRun.notify_one();
        }

        void AddSong( const sound_id id, const std::string& filePath ) override
        {
			std::unique_lock<std::mutex> lock( m_Mutex );

			if ( m_Music.find( id ) != m_Music.end() )
			{
				std::cerr << "ERROR::SDLSOUNDSYSTEMIMPL::SOUNDID_" << id << "_IS_ALREADY_IN_MUSIC\n";
				return;
			}
			m_Music[ id ] = std::make_unique<SoundPlayer>( filePath );
        }

		int MaxVolume() const override { return SoundPlayer::MaxVolume(); }

    private:
		std::unordered_map<sound_id, std::unique_ptr<SoundPlayer>> m_Music;

		std::queue<soundinfo> m_Queue;

		bool m_SoundThreadRunning{ false };
		std::condition_variable m_ConditionToRun;
		std::mutex m_Mutex;
		std::jthread m_SoundThread;
    };
}
