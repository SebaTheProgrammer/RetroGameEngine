#pragma once
#include "GameEvents.h"
#include <string>
namespace dae
{
	class OnDeathEvent : public GameEvents
	{
		public:
		OnDeathEvent( const std::string& name ): m_Name(name) {}
		~OnDeathEvent() = default;

		private:
			std::string m_Name;
	};
}