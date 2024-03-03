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

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject( const GameObject& other ) = delete;
		GameObject( GameObject&& other ) = delete;
		GameObject& operator=( const GameObject& other ) = delete;
		GameObject& operator=( GameObject&& other ) = delete;

		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y, float z = 0);
		void SetLocalPosition( float x, float y, float z = 0 );
		Transform& GetTransform() { return m_Transform; }
		Transform& GetLocalTransform() { return m_LocalTransform; }

		void AddComponent( std::shared_ptr< BaseComponent> pComponent);
		void RemoveComponent( std::shared_ptr< BaseComponent> pComponent);

		template<typename T>
		T* AddComponent()
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a component");

			for (BaseComponent* pComponent : m_pComponents)
			{
				T* pDerived = dynamic_cast<T*>(pComponent);
				if (pDerived)
				{
					return pDerived;
				}
			}

			T* pComponent = new T();
			m_pComponents.push_back(pComponent);
			pComponent->SetGameObject(this);
			return pComponent;
		}

		template <typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a component");

			for (BaseComponent* pComponent : m_pComponents)
			{
				T* pDerived = dynamic_cast<T*>(pComponent);
				if (pDerived)
				{
					return pDerived;
				}
			}
			return nullptr;
		}

		template <typename T>
		T* RemoveComponent()
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must be a component");

			for (size_t i{}; i < m_pComponents.size(); ++i)
			{
				T* pDerived = dynamic_cast<T*>(m_pComponents[i]);
				if (pDerived)
				{
					m_pComponents.erase(m_pComponents.begin() + i);
					return pDerived;
				}
			}
			return nullptr;
		}

		void AddChild(std::shared_ptr<GameObject> pChild);
		void RemoveChild(std::shared_ptr<GameObject> pChild);
		void UpdateChildren();
		void RenderChildren() const;

		void SetParent( std::shared_ptr<GameObject> pParent );

	private:
		Transform m_Transform{};
		Transform m_LocalTransform{};

		std::vector < std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector < std::shared_ptr<GameObject>> m_pChildren{};
		std::shared_ptr<GameObject> m_pParent{};
	};
}
