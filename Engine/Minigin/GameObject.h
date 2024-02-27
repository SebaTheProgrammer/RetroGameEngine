#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* pComponent);
		void RemoveComponent(BaseComponent* pComponent);

	private:
		Transform m_Transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_Texture{};

		std::vector<BaseComponent*> m_pComponents{};
	};
}
