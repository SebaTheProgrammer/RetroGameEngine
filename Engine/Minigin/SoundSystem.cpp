#include "SoundSystem.h"

dae::SoundSystem::~SoundSystem()
{
}

dae::LoggingSoundSystem::~LoggingSoundSystem()
{
}

//door unique ptrs vind hij de default destructor niet... cpp helpt hierbij

dae::SDLSoundSystem::~SDLSoundSystem()
{
}
