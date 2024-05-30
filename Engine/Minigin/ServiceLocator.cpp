#include "ServiceLocator.h"
#include "SoundSystem.h"

namespace dae
{
	std::unique_ptr<SoundSystem> ServiceLocator::s_SoundSystemInstance = std::make_unique<NullSoundSystem>();

	ServiceLocator::~ServiceLocator() = default;

	SoundSystem& ServiceLocator::GetSoundSystem()
	{
		return *s_SoundSystemInstance;
	}

	void ServiceLocator::RegisterSoundSystem( std::unique_ptr<SoundSystem> ss )
	{
		if ( ss == nullptr ) 
		{
			s_SoundSystemInstance = std::make_unique<NullSoundSystem>();
		}
		else 
		{
			s_SoundSystemInstance = std::move( ss );
		}
	}
	void ServiceLocator::CleanUp()
	{
		s_SoundSystemInstance.get()->~SoundSystem();
	}
}