#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	/*for ( int index{ 0 };index< m_Components.size();++index )
	{
		m_Components[ index ].Update();
	}*/
}

void dae::GameObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

	/*for ( int index{ 0 }; index < m_Components.size(); ++index )
	{
		m_Components[ index ].Render();
	}*/
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
