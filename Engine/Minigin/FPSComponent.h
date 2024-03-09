#pragma once
#include <string>
#include "TextComponent.h"
#include "BaseComponent.h"

namespace dae
{
	class BaseComponent;

	class FPSComponent : public TextComponent
	{

	public:
		FPSComponent( GameObject* const parentGameObject, const std::string& text, std::shared_ptr<Font> font );
		virtual ~FPSComponent() = default;

		FPSComponent( const FPSComponent& other ) = delete;
		FPSComponent( FPSComponent&& other ) = delete;
		FPSComponent& operator=( const FPSComponent& other ) = delete;
		FPSComponent& operator=( FPSComponent&& other ) = delete;

		virtual void Update() override;
	};
}
