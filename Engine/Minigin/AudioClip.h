#pragma once
#include <string>
#include "ResourceManager.h"
#include <SDL_mixer.h>

class AudioClip final
{
public:
	AudioClip( std::string filepath )
	{
		m_AudioClipImpl = new AudioClipImpl( filepath );
	}
	~AudioClip()
	{
		delete m_AudioClipImpl;
	}

	void Load()
	{
		m_AudioClipImpl->Load();
	}

	void Play( int volume )
	{
		m_AudioClipImpl->Play( volume );
	}

	bool IsLoaded() const
	{
		return m_AudioClipImpl->IsLoaded();
	}


	class AudioClipImpl;
	AudioClipImpl* m_AudioClipImpl;

	class AudioClipImpl final
	{
	public:
		AudioClipImpl( const std::string& path ) : m_AudioPath{ path }
		{
		}

		~AudioClipImpl()
		{
			Unload();
		}

		void Load()
		{
			if ( !m_pChunk )
			{
				m_pChunk = Mix_LoadWAV( (dae::ResourceManager::GetInstance().GetDataPath() + m_AudioPath).c_str() );

				if ( !m_pChunk )
				{
					std::cout << "Couldn't load audio clip: " << ( dae::ResourceManager::GetInstance().GetDataPath() + m_AudioPath ).c_str() << "\n";
				}
			}
		}

		void Unload()
		{
			if ( m_pChunk )
			{
				Mix_FreeChunk( m_pChunk );
				m_pChunk = nullptr;
			}
		}

		void Play( int volume )
		{
			if ( m_pChunk )
			{
				Mix_VolumeChunk( m_pChunk, static_cast< int >( MIX_MAX_VOLUME * volume ) );
				int channel = Mix_PlayChannel( -1, m_pChunk, 0 );

				if ( channel == -1 )
				{
					std::cout << "No free channel to play audio clip: " << m_AudioPath << "\n";
				}
			}
		}

		bool IsLoaded() const
		{
			return ( m_pChunk != nullptr );
		}

	private:
		std::string m_AudioPath;
		Mix_Chunk* m_pChunk{ nullptr };
	};

};

