#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include <iostream>

dae::TextureComponent::TextureComponent( GameObject* parentGameObject, const std::string& fileName )
	: BaseComponent( parentGameObject )
{
		m_pTexture = ResourceManager::GetInstance().LoadTexture( fileName );
}

dae::TextureComponent::TextureComponent( GameObject* parentGameObject, const std::shared_ptr<Texture2D> texture )
	: BaseComponent( parentGameObject )
{
	m_pTexture = texture;
}

void dae::TextureComponent::Update()
{
	if ( m_pTexture )
	{
		const auto& pos = m_LocalTransform.GetPosition() + GetOwner()->GetWorldTransform().GetPosition();

		m_X = pos.x;
		m_Y = pos.y;
	}
}

void dae::TextureComponent::Render() const
{
	if ( m_pTexture )
	{
		Renderer::GetInstance().RenderTexture( *m_pTexture, m_X, m_Y );
	}
}

void dae::TextureComponent::SetTexture( const std::string& filename )
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture( filename );
}
