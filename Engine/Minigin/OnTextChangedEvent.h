#pragma once
#include "GameEvents.h"
#include <string>
namespace dae
{
	class OnTextChangedEvent : public GameEvents
	{
	public:
		OnTextChangedEvent( const std::string& text ) : m_Text( text ) {}
		~OnTextChangedEvent() = default;

	private:
		std::string m_Text;
	};
}