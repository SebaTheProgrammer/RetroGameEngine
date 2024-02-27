#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() 
{
	for (auto pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent= nullptr;
	}
	m_pComponents.clear();
}

void dae::GameObject::AddComponent( BaseComponent* pComponent )
{
	m_pComponents.emplace_back(pComponent);
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
		for( auto pComponent : m_pComponents )
		{
			pComponent->Update();
		}
}

void dae::GameObject::Render() const
{
	for ( auto pComponent : m_pComponents )
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
