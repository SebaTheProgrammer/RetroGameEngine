#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <iostream>

void dae::GameObject::AddComponent( std::shared_ptr< BaseComponent> pComponent )
{
	m_pComponents.emplace_back( std::move( pComponent ) );
}

void dae::GameObject::RemoveComponent( std::shared_ptr< BaseComponent> pComponent )
{
	m_pComponents.erase( std::remove( m_pComponents.begin(), m_pComponents.end(), pComponent ), m_pComponents.end() );
}

void dae::GameObject::AddChild( std::shared_ptr<GameObject> pChild )
{
	//pChild->SetParent( shared_from_this() );
	m_pChildren.emplace_back( std::move( pChild ) );
}

void dae::GameObject::RemoveChild( std::shared_ptr<GameObject> pChild )
{
	m_pChildren.erase( std::remove( m_pChildren.begin(), m_pChildren.end(), pChild ), m_pChildren.end() );
}

void dae::GameObject::SetParent( std::shared_ptr<GameObject> pParent )
{
	if ( pParent != nullptr )
	{
		m_pParent = pParent;
	}
}

void dae::GameObject::UpdateChildren()
{
	for ( auto& pChild : m_pChildren )
	{
		pChild->Update();
	}
}

void dae::GameObject::RenderChildren() const
{
	for ( const auto& pChild : m_pChildren )
	{
		pChild->Render();
	}
}

void dae::GameObject::Update()
{
	for ( auto& pComponent : m_pComponents )
	{
		pComponent->Update();
	}

	UpdateChildren();
}

void dae::GameObject::Render() const
{
	RenderChildren();

	for ( auto& pComponent : m_pComponents )
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z );

	for ( const auto& pChild : m_pChildren )
	{
		pChild->SetPosition( x, y, z );
	}
}

void dae::GameObject::SetLocalPosition( float x, float y, float z )
{
	m_LocalTransform.SetPosition( x, y, z );

	for ( const auto& pChild : m_pChildren )
	{
		pChild->SetLocalPosition( x, y, z );
	}
}
