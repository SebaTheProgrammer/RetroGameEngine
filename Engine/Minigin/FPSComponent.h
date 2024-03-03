#pragma once
#include <string>
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public TextComponent
	{

	public:
		FPSComponent() = default;
		virtual ~FPSComponent() = default;

		FPSComponent( const FPSComponent& other ) = delete;
		FPSComponent( FPSComponent&& other ) = delete;
		FPSComponent& operator=( const FPSComponent& other ) = delete;
		FPSComponent& operator=( FPSComponent&& other ) = delete;

		void Update() override;
	};
}
