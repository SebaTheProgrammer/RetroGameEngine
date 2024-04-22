#pragma once
#include <string>
#include <memory>
#include <map>
#include "Singleton.h"

using sound_id = unsigned short;

namespace dae
{
	class SoundSystem
	{
	public:
		friend class Singleton<SoundSystem>;
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		virtual void PlaySound( sound_id, const float )
		{

		}
		virtual void PauseSound( sound_id )
		{

		}
	};
}
