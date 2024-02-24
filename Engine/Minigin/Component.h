#pragma once
#include <string>
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:

		Component();
		virtual ~Component();
		Component( const Component& other ) = delete;
		Component( Component&& other ) = delete;
		Component& operator=( const Component& other ) = delete;
		Component& operator=( Component&& other ) = delete;

		virtual void Update();

		void SetText( const std::string& text );
		void SetPosition( float x, float y );

	private:

	};
}

