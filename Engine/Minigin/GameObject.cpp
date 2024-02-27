#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent( BaseComponent* pComponent )
{
	m_pComponents.push_back(pComponent);
}

void dae::GameObject::RemoveComponent( BaseComponent* pComponent )
{
	auto it = std::find( m_pComponents.begin(), m_pComponents.end(), pComponent );

	if ( it != m_pComponents.end() )
	{
		m_pComponents.erase( it );
	}
}

void dae::GameObject::Update()
{
	for ( BaseComponent* pComponent : m_pComponents )
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	if ( m_Texture != nullptr ) {
		Renderer::GetInstance().RenderTexture( *m_Texture, pos.x, pos.y );
	}
	for ( const BaseComponent* pComponent : m_pComponents )
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
