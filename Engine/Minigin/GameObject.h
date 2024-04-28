#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:

		GameObject( int sceneIndex = -1) { m_SceneIndex = sceneIndex; };

		~GameObject();
		GameObject( const GameObject& other ) = delete;
		GameObject( GameObject&& other ) = delete;
		GameObject& operator=( const GameObject& other ) = delete;
		GameObject& operator=( GameObject&& other ) = delete;


		void Initialize();

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		bool AddComponent( std::shared_ptr<BaseComponent> component );

		template<typename T>
		std::shared_ptr<T> GetComponent()
		{
			for ( auto& component : m_pComponents )
			{
				if ( auto castedComponent = std::dynamic_pointer_cast< T >( component ) )
				{
					return castedComponent;
				}
			}
			return nullptr;
		}
		template<typename T>
		void RemoveComponent()
		{
			for ( auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it )
			{
				if ( std::dynamic_pointer_cast< T >( *it ) )
				{
					m_pComponents.erase( it );
					return;
				}
			}
		}

		void ClearComponents() { m_pComponents.clear(); }

		void SetParent( GameObject* parent, bool keepWorldPosition = true );
		GameObject* GetParent() const { return m_Parent; }

		size_t GetChildCount() const { return m_pChildren.size(); }
		std::shared_ptr<GameObject> GetChildSharedPtr( GameObject* child ) const;
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const { return m_pChildren; }

		void SetLocalTransform( Transform transform );
		void AddLocalTransform( Transform transform );

		void SetWorldTransformDirty();

		Transform GetLocalTransform() const { return m_LocalTransform; }
		Transform GetWorldTransform();

		int GetSceneIndex() const { return m_SceneIndex; }

	private:
		Transform m_WorldTransform{};
		Transform m_LocalTransform{};
		bool m_IsTransformDirty{false};

		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
		GameObject* m_Parent{};

		void AddChild( std::shared_ptr<GameObject>child );
		void RemoveChild( GameObject* child );
		void UpdateChildren();
		void LateUpdateChildren();
		void RenderChildren() const;

		void UpdateWorldTransform();

		bool IsChild( GameObject* gameObject );

		int m_SceneIndex{ -1 };
	};
}

