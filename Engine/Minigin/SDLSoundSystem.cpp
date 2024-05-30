#include "SoundSystem.h"
#include "AudioClip.h"
#include <SDL_mixer.h>
#include <sdl.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace dae;

class SDLSoundSystem::SoundSystemImpl final {
public:
    SoundSystemImpl() : m_SoundThread( &SoundSystemImpl::AudioThread, this ) 
    {
        if ( SDL_Init( SDL_INIT_AUDIO ) < 0 ) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        }

        if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        }
    }

    ~SoundSystemImpl() {
        if ( m_SoundThread.joinable() ) 
        {
            m_SoundThread.request_stop();
            m_SoundThread.join();
        }
        m_SoundThread.request_stop();
        m_SoundThread.join();
    }

    unsigned short AddSound( const std::string& name, const std::string& path ) {
        std::lock_guard<std::mutex> lock{ m_Mutex };
        auto it = m_MapSoundId.find( name );
        if ( it != m_MapSoundId.end() ) {
            return it->second;
        }

        auto id = static_cast< unsigned short >( m_AudioClips.size() );
        m_MapSoundId.emplace( name, id );
        m_AudioClips.emplace_back( std::make_unique<AudioClip>( path ) );
        return id;
    }

    void Play( unsigned short id, int volume ) {
        {
            std::lock_guard<std::mutex> lock{ m_Mutex };
            m_SoundQueue.emplace( SoundEvent{ id, volume } );
        }
        m_Condition.notify_one();
    }

    void Pause() {
        Mix_Pause( -1 );
    }

    void Resume() {
        Mix_Resume( -1 );
    }

    void Mute() {
        m_Volume = Mix_Volume( -1, 0 );
    }

    void Unmute() {
        if ( m_Volume >= 0 ) {
            Mix_Volume( -1, m_Volume );
            m_Volume = -1;
        }
    }

    void SetVolume( int volume ) 
    {
        Mix_Volume( -1, static_cast< int >( MIX_MAX_VOLUME * volume ) );
    }

    int GetVolume() 
    {
		return m_Volume;
	}

    unsigned short GetSoundId( const std::string& name )
    {
        auto it = m_MapSoundId.find( name );
        if ( it != m_MapSoundId.end() ) {
            return it->second;
        }
        return 0;
    }

private:
    struct SoundEvent {
        unsigned short id;
        int volume;
    };

    void AudioThread() {
        while ( true ) {
            std::unique_lock<std::mutex> lock{ m_Mutex };
            m_Condition.wait( lock, [ this ] { return !m_SoundQueue.empty(); } );

            auto [id, volume] = m_SoundQueue.front();
            m_SoundQueue.pop();

            auto pAudioClip = m_AudioClips[ id ].get();
            lock.unlock();

            if ( !pAudioClip->IsLoaded() ) pAudioClip->Load();
            pAudioClip->Play( volume );
        }
    }

    std::jthread m_SoundThread;
    std::mutex m_Mutex;
    std::condition_variable m_Condition;
    std::unordered_map<std::string, unsigned short> m_MapSoundId;
    std::vector<std::unique_ptr<AudioClip>> m_AudioClips;
    std::queue<SoundEvent> m_SoundQueue;
    int m_Volume{ 1 };
};

SDLSoundSystem::SDLSoundSystem()
    : m_pImplSoundSystem( std::make_unique<SoundSystemImpl>() ) {}

SDLSoundSystem::~SDLSoundSystem() 
{
    Mix_Quit();
    SDL_Quit();

    if ( m_pImplSoundSystem )
    {
		m_pImplSoundSystem.reset();
	}
}

unsigned short SDLSoundSystem::AddSound( const std::string& name, const std::string& path ) {
    return m_pImplSoundSystem->AddSound( name, path );
}

unsigned short dae::SDLSoundSystem::GetSoundId( const std::string& name )
{
    return m_pImplSoundSystem->GetSoundId( name );
}

void SDLSoundSystem::Play( unsigned short id, int volume ) {
    m_pImplSoundSystem->Play( id, volume );
}

void SDLSoundSystem::Pause() {
    m_pImplSoundSystem->Pause();
}

void SDLSoundSystem::Resume() {
    m_pImplSoundSystem->Resume();
}

void SDLSoundSystem::Mute() {
    m_pImplSoundSystem->Mute();
}

void SDLSoundSystem::Unmute() {
    m_pImplSoundSystem->Unmute();
}

void SDLSoundSystem::SetVolume( int volume ) {
    m_pImplSoundSystem->SetVolume( volume );
}

int dae::SDLSoundSystem::GetVolume()
{
    return m_pImplSoundSystem->GetVolume();
}
