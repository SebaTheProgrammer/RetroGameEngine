#include "FPSComponent.h"
#include "GameTime.h"
#include "Renderer.h"
#include <iostream>
#include "TextComponent.h"

dae::FPSComponent::FPSComponent( GameObject* const parentGameObject, const std::string& text, std::shared_ptr<Font> font )
	: TextComponent( parentGameObject, text, font ) 
{
}

void dae::FPSComponent::Update()
{
	TextComponent::Update();

	const float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
	TextComponent::SetText( ( "FPS: " + std::to_string( int( 1.0f / deltaTime ) ) ) );
}
