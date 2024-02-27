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

}

void dae::TextureComponent::Render() const
{
	if( m_pTexture )
		{
				//const auto pos = m_pGameObject->GetTransform().GetPosition();
				//Renderer::GetInstance().RenderTexture( *m_pTexture, pos.x, pos.y );
		}
}
