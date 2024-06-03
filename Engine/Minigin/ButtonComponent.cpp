#include "ButtonComponent.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

dae::ButtonComponent::ButtonComponent( GameObject* const parentGameObject, const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<dae::Command> command)
	: BaseComponent( parentGameObject ),
	m_Command{ command }
{
	m_TextComponent = std::make_shared<TextComponent>( parentGameObject, text, font );
	m_TextComponent->SetPosition( 0, 0 );

	this->BindAction( command );
}

void dae::ButtonComponent::Update()
{
	m_TextComponent->Update();
}

void dae::ButtonComponent::Render() const
{
	m_TextComponent->Render();
}

void dae::ButtonComponent::Clicked()
{
	if ( m_Command )
	{
		m_Command->Execute();
	}
}

void dae::ButtonComponent::SetText( const std::string& text )
{
	m_TextComponent->SetText( text );
}

void dae::ButtonComponent::SetLocalPosition( float x, float y )
{
	m_TextComponent->SetPosition( x, y );
}
