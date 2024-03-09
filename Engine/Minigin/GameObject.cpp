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
	//pos
	if ( keepWorldPosition )
	{
		if ( parent == nullptr )
		{
			SetLocalTransform( GetWorldTransform() );
		}
		else
		{
			SetLocalTransform(
				GetWorldTransform().GetPosition().x + parent->GetWorldTransform().GetPosition().x,
				GetWorldTransform().GetPosition().y + parent->GetWorldTransform().GetPosition().y,
				GetWorldTransform().GetPosition().z + parent->GetWorldTransform().GetPosition().z );
		}
	}
	else
	{
		SetWorldTransformDirty();
	}
	//clearing previous parent
	std::shared_ptr<GameObject> thisPtr{};
	if ( m_Parent )

	{
		thisPtr = m_Parent->GetChildSharedPtr( this );
	}
	else
	{
		auto scene{ SceneManager::GetInstance().GetCurrentScene() };
		thisPtr = scene->GetChildSharedPtr( this );
	}
	if ( m_Parent )
	{
		m_Parent->RemoveChild( this );
	}
	else
	{
		auto scene{ SceneManager::GetInstance().GetCurrentScene() };
		scene->DettatchFromRoot( this );
	}

	//setting new parent
	m_Parent = parent;

	if ( m_Parent )
	{
		m_Parent->AddChild( thisPtr );
	}
	else
	{
		auto scene{ SceneManager::GetInstance().GetCurrentScene() };
		scene->AttatchToRoot( thisPtr );
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

void dae::GameObject::SetLocalTransform( float x, float y, float z )
{
	m_LocalTransform.SetPosition( x, y, z );
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
			m_WorldTransform.SetPosition(
				m_Parent->GetWorldTransform().GetPosition().x + m_Parent->GetLocalTransform().GetPosition().x,
				m_Parent->GetWorldTransform().GetPosition().y + m_Parent->GetLocalTransform().GetPosition().y,
				m_Parent->GetWorldTransform().GetPosition().z + m_Parent->GetLocalTransform().GetPosition().z );
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

