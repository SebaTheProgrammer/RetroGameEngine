#include "FPSComponent.h"
#include "GameTime.h"
#include "Renderer.h"
#include <iostream>

void dae::FPSComponent::Update()
{
	TextComponent::Update();

	const float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
	m_Text = "FPS: " + std::to_string( int( 1.0f / deltaTime ) );
	TextComponent::SetText(m_Text);
}
