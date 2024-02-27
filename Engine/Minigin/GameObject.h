#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "TextComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject( const GameObject& other ) = delete;
		GameObject( GameObject&& other ) = delete;
		GameObject& operator=( const GameObject& other ) = delete;
		GameObject& operator=( GameObject&& other ) = delete;

		void Update();
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

	private:
		Transform m_Transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_Texture{};

		static std::vector<Component> m_Components;
	};
}
