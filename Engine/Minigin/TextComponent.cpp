#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "ResourceManager.h"
#include "GameTime.h"
#include <iostream>

dae::TextComponent::TextComponent( GameObject* parentGameObject, const std::string& text, std::shared_ptr<Font> font, bool standStill)
	: BaseComponent( parentGameObject )
	, m_NeedsUpdate( true )
	, m_Text( text )
	, m_Font( std::move( font ) )
	, m_TextTexture( nullptr )
	, m_StandStill(standStill)
{ 
	const SDL_Color color = { 255,255,255,255 };
	const auto surf = TTF_RenderText_Blended( m_Font->GetFont(), m_Text.c_str(), color );
	if ( surf == nullptr )
	{
		throw std::runtime_error( std::string( "Render text failed: " ) + SDL_GetError() );
	}
	auto texture = SDL_CreateTextureFromSurface( Renderer::GetInstance().GetSDLRenderer(), surf );
	if ( texture == nullptr )
	{
		throw std::runtime_error( std::string( "Create text texture from surface failed: " ) + SDL_GetError() );
	}
	SDL_FreeSurface( surf );
	m_TextTexture = std::make_shared<Texture2D>( texture );
}

void dae::TextComponent::Update()
{
	if ( m_NeedsUpdate )
	{
		const SDL_Color color = { 255,255,255,255 }; 
		const auto surf = TTF_RenderText_Blended( m_Font->GetFont(), m_Text.c_str(), color );
		if ( surf == nullptr )
		{
			throw std::runtime_error( std::string( "Render text failed: " ) + SDL_GetError() );
		}
		auto texture = SDL_CreateTextureFromSurface( Renderer::GetInstance().GetSDLRenderer(), surf );
		if ( texture == nullptr )
		{
			throw std::runtime_error( std::string( "Create text texture from surface failed: " ) + SDL_GetError() );
		}
		SDL_FreeSurface( surf );
		m_TextTexture = std::make_shared<Texture2D>( texture );
		m_NeedsUpdate = false;

		if ( m_StandStill ) 
		{
			m_Transform = m_LocalTransform.GetPosition();
		}
		else
		{
			m_Transform = m_LocalTransform.GetPosition() + GetOwner()->GetWorldTransform().GetPosition();
		}
	}
}

void dae::TextComponent::Render() const
{
	if ( m_TextTexture != nullptr )
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture( *m_TextTexture, pos.x, pos.y );
	}
}

void dae::TextComponent::SetText( const std::string& text )
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition( float x, float y )
{
	m_Transform.SetPosition( x, y, 0.0f );
}


