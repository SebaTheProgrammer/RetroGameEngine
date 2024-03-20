#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include <iostream>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(object);
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Initialize()
{
	for ( auto& gameObject : m_Objects )
	{
		gameObject->Initialize();
	}
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{

}
void Scene::LateUpdate()
{
	for ( auto& gameObject : m_Objects )
	{
		gameObject->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::AttachToRoot( std::shared_ptr<GameObject> gameObject )
{
	m_Objects.emplace_back( gameObject );
}

void Scene::DettachFromRoot( GameObject* gameObject )
{
	auto it = m_Objects.begin();
	while ( it != m_Objects.end() )
	{
		auto& child = *it;
		if ( child.get() == gameObject )
		{
			it = m_Objects.erase( it );
			return;
		}
		++it;
	}
}

std::shared_ptr<GameObject> Scene::GetChildSharedPtr( GameObject* child )
{
	for ( auto& currentChild : m_Objects )
	{
		if ( currentChild.get() == child )
		{
			return currentChild;
		}
	}
	return nullptr;
}



