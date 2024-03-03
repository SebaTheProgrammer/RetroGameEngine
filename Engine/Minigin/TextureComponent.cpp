#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent( const std::string& filename )
{
		m_pTexture = ResourceManager::GetInstance().LoadTexture( filename );
}

void dae::TextureComponent::Update()
{
	if ( m_pTexture )
	{
		m_X = m_pGameObject->GetLocalTransform().GetPosition().x + m_pGameObject->GetTransform().GetPosition().x;
		m_Y = m_pGameObject->GetLocalTransform().GetPosition().y + m_pGameObject->GetTransform().GetPosition().y;
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
