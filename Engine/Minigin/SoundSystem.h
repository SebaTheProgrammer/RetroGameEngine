#pragma once
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include <iostream>
#include <SDL_mixer.h>
#include <thread>
#include <mutex>

using sound_id = unsigned short;

namespace dae
{
    class AudioClip
    {
    public:
        AudioClip( const std::string& filePath )
            : filePath( filePath ), loaded( false ), chunk( nullptr ) {}

        ~AudioClip()
        {
            std::lock_guard<std::mutex> lock( mutex );
            if ( chunk ) {
                Mix_FreeChunk( chunk );
            }
        }

        AudioClip( const AudioClip& other ) = delete;
        AudioClip( AudioClip&& other ) = delete;
        AudioClip& operator=( const AudioClip& other ) = delete;
        AudioClip& operator=( AudioClip&& other ) = delete;

        void Load()
        {
            std::lock_guard<std::mutex> lock( mutex );
            if ( !loaded )
            {
                std::thread loadThread( [ this ] { std::lock_guard<std::mutex> threadLock( mutex );
                chunk = Mix_LoadWAV( filePath.c_str() );
                if ( chunk == nullptr )
                {
                    std::cerr << "Failed to load audio clip: " << filePath << std::endl;
                }
                else
                {
                    loaded = true;
                }
                    } );
                loadThread.detach();
            }
        }

        void Play()
        {
            std::lock_guard<std::mutex> lock( mutex );
            if ( loaded && chunk ) {
                Mix_PlayChannel( -1, chunk, 0 );
            }
        }

        void Pause()
        {
            std::lock_guard<std::mutex> lock( mutex );
            if ( loaded && chunk ) {
                Mix_HaltChannel( -1 );
            }
        }

        void SetVolume( float volume )
        {
            std::lock_guard<std::mutex> lock( mutex );
            if ( chunk ) {
                int intVolume = static_cast< int >( ( volume / 100.0f ) * MIX_MAX_VOLUME );
                intVolume = clamp( intVolume, 0, MIX_MAX_VOLUME );
                Mix_VolumeChunk( chunk, intVolume );
            }
        }

        bool IsLoaded()
        {
            std::lock_guard<std::mutex> lock( mutex );
            return loaded;
        }

    private:
        int clamp( int value, int minValue, int maxValue )
        {
            if ( value < minValue ) {
                return minValue;
            }
            else if ( value > maxValue ) {
                return maxValue;
            }
            return value;
        }

        std::string filePath;
        bool loaded;
        Mix_Chunk* chunk;
        std::mutex mutex;
    };

    class SoundSystem
    {
    public:
        friend class Singleton<SoundSystem>;
        SoundSystem() = default;
        virtual ~SoundSystem() {};

        virtual void Play( sound_id, const float ) {};

        virtual void PauseSound( const sound_id ) {};

        virtual void AddAudioClip( const sound_id, const std::shared_ptr<AudioClip>& ) {};
    };

    class NullSoundSystem final : public SoundSystem
    {
        void Play( const sound_id, const float ) override {}
    };

    class LoggingSoundSystem final : public SoundSystem
    {
        std::unique_ptr<SoundSystem> _real_ss;
    public:
        LoggingSoundSystem( std::unique_ptr<SoundSystem>&& ss ) : _real_ss( std::move( ss ) ) {}
        virtual ~LoggingSoundSystem() {};

        void Play( sound_id id, const float volume ) override
        {
            _real_ss->Play( id, volume );
            std::cout << "playing " << id << " at volume " << volume << std::endl;
        }
    };

    class SDLSoundSystem final : public SoundSystem
    {
    public:
        SDLSoundSystem() { if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 4, 2048 ) < 0 ) { return; } }

        ~SDLSoundSystem() override { Mix_CloseAudio(); }

        void Play( const sound_id id, const float volume = 100 ) override
        {
            auto audioclip = audioclips[ id ];

            if ( !audioclip->IsLoaded() ) audioclip->Load();

            audioclip->SetVolume( volume );

            audioclip->Play();
        }

        void PauseSound( const sound_id id )
        {
            auto audioclip = audioclips[ id ];

            if ( !audioclip->IsLoaded() )
                audioclip->Load();

            audioclip->Pause();
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
        std::map<sound_id, std::shared_ptr<AudioClip>> audioclips{};
    };
}
