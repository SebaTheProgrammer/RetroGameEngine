#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

dae::GameObject::~GameObject() = default;

void dae::GameObject::Initialize()
{
	for ( auto& component : m_pComponents )
	{
		component->Initialize();
	}
	for ( auto& child : m_pChildren )
	{
		child->Initialize();
	}
}

void dae::GameObject::Update()
{
	for ( auto& component : m_pComponents )
	{
		component->Update();
	}

	UpdateChildren();
}

void dae::GameObject::FixedUpdate()
{
	for ( auto& child : m_pChildren )
	{
		child->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{
	for ( auto& component : m_pComponents )
	{
		component->Update();
	}
	
	LateUpdateChildren();
}

void dae::GameObject::Render() const
{
	for ( auto& component : m_pComponents )
	{
		component->Render();
	}
	
	RenderChildren();
}

void dae::GameObject::SetParent( GameObject* parent, bool keepWorldPosition )
{
	if ( IsChild( parent ) || parent == this || parent == m_Parent )
	{
		return;
	}

	if ( keepWorldPosition )
	{
		if ( parent == nullptr )
		{
			SetLocalTransform( GetWorldTransform() );
		}
		else
		{
			SetLocalTransform( GetWorldTransform() + parent->GetWorldTransform().GetPosition() );
		}
	}
	else
	{
		SetWorldTransformDirty();
	}

	std::shared_ptr<GameObject> thisSharedPtr{};
	if ( m_Parent )
	{
		thisSharedPtr = m_Parent->GetChildSharedPtr( this );
		m_Parent->RemoveChild( this );
	}
	else
	{
		auto currentScene = SceneManager::GetInstance().GetCurrentScene();
		thisSharedPtr = currentScene->GetChildSharedPtr( this );
		currentScene->DettachFromRoot( this );
	}

	// Set the new parent
	m_Parent = parent;
	if ( m_Parent )
	{
		m_Parent->AddChild( thisSharedPtr );
	}
	else
	{
		auto currentScene = SceneManager::GetInstance().GetCurrentScene();
		currentScene->AttachToRoot( thisSharedPtr );
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildSharedPtr( GameObject* child ) const
{
	for ( auto& currentChild : m_pChildren )
	{
		if ( currentChild.get() == child )
		{
			return currentChild;
		}
	}
	return nullptr;
}

void dae::GameObject::RemoveChild( GameObject* child )
{
	for ( auto it{ m_pChildren.begin() }; it != m_pChildren.end(); ++it )
	{
		if ( ( *it ).get() == child )
		{
			m_pChildren.erase( it );
			return;
		}
	}
}

void dae::GameObject::UpdateChildren()
{
	for ( auto& child : m_pChildren )
	{
		child->Update();
	}
}

void dae::GameObject::LateUpdateChildren()
{
	for ( auto& child : m_pChildren )
	{
		child->LateUpdate();
	}
}

void dae::GameObject::RenderChildren() const
{
	for ( auto& child : m_pChildren )
	{
		child->Render();
	}
}

void dae::GameObject::SetLocalTransform( Transform transform )
{
	m_LocalTransform = transform;
	SetWorldTransformDirty();
}

void dae::GameObject::AddLocalTransform( Transform transform )
{
	m_LocalTransform += transform;
	SetWorldTransformDirty();
}

void dae::GameObject::SetWorldTransformDirty()
{
	m_IsTransformDirty = true;

	for ( auto& child : m_pChildren )
	{
		child->SetWorldTransformDirty();
	}
}

dae::Transform dae::GameObject::GetWorldTransform()
{
	if ( m_IsTransformDirty )
	{
		UpdateWorldTransform();
	}
	return m_WorldTransform;
}

void dae::GameObject::UpdateWorldTransform()
{
	if ( m_IsTransformDirty )
	{
		if ( m_Parent != nullptr )
		{
			m_WorldTransform = m_Parent->GetWorldTransform() + m_LocalTransform;
		}
		else
		{
			m_WorldTransform = m_LocalTransform;
		}
		m_IsTransformDirty = false;
	}
}

void dae::GameObject::AddChild( std::shared_ptr<GameObject> child )
{
	m_pChildren.emplace_back( child );
}

bool dae::GameObject::IsChild( GameObject* gameObject )
{
	if ( gameObject == nullptr ) return false;

	for ( auto& child : m_pChildren )
	{
		if ( child.get() == gameObject )
			return true;
	}
	return false;
}

bool dae::GameObject::AddComponent( std::shared_ptr<BaseComponent> component )
{
	if ( component.get() )
	{
		m_pComponents.emplace_back( component );
		return true;
	}
	return false;
}

