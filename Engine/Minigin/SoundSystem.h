#pragma once
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"
#include <iostream>
//#include <SDL_mixer.h>

using sound_id = unsigned short;

namespace dae
{
 //   class AudioClip
 //   {
 //   public:

 //       AudioClip( const std::string& filePath )
 //           : filePath( filePath ), loaded( false ), chunk( nullptr )
 //       {}

 //       ~AudioClip()
 //       {
 //           if ( chunk )
 //           {
 //              // Mix_FreeChunk( chunk );
 //           }
 //       }

 //       void Load()
 //       {
 //           if ( !loaded )
 //           {
 //               //chunk = Mix_LoadWAV( filePath.c_str() );
 //               if ( chunk == nullptr )
 //               {
 //                   std::cerr << "Failed to load audio clip: " << filePath << std::endl;
 //               }
 //               else
 //               {
 //                   loaded = true;
 //               }
 //           }
 //       }

 //       void Play()
 //       {
 //           if ( loaded && chunk )
 //           {
 //               //Mix_PlayChannel( -1, chunk, 0 );
 //           }
 //       }

 //       void Pause()
 //       {
 //           if ( loaded && chunk )
 //           {
 //              // Mix_HaltChannel( -1 );
 //           }
 //       }

 //       void SetVolume( float volume )
 //       {
 //           if ( chunk )
 //           {
 //               //int intVolume = static_cast< int >( ( volume / 100 ) * MIX_MAX_VOLUME );
 //              // Mix_VolumeChunk( chunk, intVolume );
 //           }
 //       }

 //       bool IsLoaded() const
 //       {
 //           return loaded;
 //       }

 //   private:
 //       std::string filePath;
 //       bool loaded;
 //      // Mix_Chunk* chunk;
 //   };

	//class SoundSystem
	//{
	//public:
	//	friend class Singleton<SoundSystem>;
	//	SoundSystem() = default;
	//	virtual ~SoundSystem();

	//	virtual void Play( sound_id, const float)
	//	{
	//	}

 //       virtual void PauseSound( const sound_id )
 //       {
	//	}

 //       virtual void AddAudioClip( const sound_id, const std::shared_ptr<AudioClip>& )
 //       {
	//	}
	//};

	//class NullSoundSystem final : public SoundSystem
	//{
	//	void Play( const sound_id, const float ) override {}
	//};

	//class LoggingSoundSystem final : public SoundSystem
	//{
	//	std::unique_ptr<SoundSystem> _real_ss;
	//public:
	//	LoggingSoundSystem( std::unique_ptr<SoundSystem>&& ss ) : _real_ss( std::move( ss ) ) {}
	//	virtual ~LoggingSoundSystem();

	//	void Play( sound_id id, const float volume ) override
	//	{
	//		_real_ss->Play( id, volume );
	//		std::cout << "playing " << id << " at volume " << volume << std::endl;
	//	}
	//};

	//class SDLSoundSystem final : public SoundSystem
	//{
	//public:

	//	~SDLSoundSystem() override;

	//	void Play( const sound_id id, const float volume = 100 ) override
	//	{
	//		auto audioclip = audioclips[ id ];

	//		if ( !audioclip->IsLoaded() )
	//			audioclip->Load();

	//		audioclip->SetVolume( volume );

	//		audioclip->Play();
	//	}

	//	void PauseSound( const sound_id id )
	//	{
	//		auto audioclip = audioclips[ id ];

	//		if ( !audioclip->IsLoaded() )
	//			audioclip->Load();

	//		audioclip->Pause();
	//	}

	//	void AddAudioClip( const sound_id id, const std::shared_ptr<AudioClip>& audioclip )
	//	{
	//		audioclips[ id ] = audioclip;
	//	}

	//	void RemoveAudioClip( const sound_id id )
	//	{
	//		audioclips.erase( id );
	//	}

	//private:
	//	std::map<sound_id, std::shared_ptr<AudioClip>> audioclips{};
	//};
}
