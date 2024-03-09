#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:

		virtual ~BaseComponent() = default;
		BaseComponent( const BaseComponent& other ) = delete;
		BaseComponent( BaseComponent&& other ) = delete;
		BaseComponent& operator=( const BaseComponent& other ) = delete;
		BaseComponent& operator=( BaseComponent&& other ) = delete;

		virtual void Initialize() {};

		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		inline void SetLocalPosition( float x, float y, float z = 0.f ) { m_LocalTransform.SetPosition( x, y, z ); }

	protected:

		BaseComponent( GameObject* pParent );

		GameObject* GetOwner() const { return m_pGameObject; }
		Transform m_LocalTransform{};

	private:

		GameObject* m_pGameObject;
	};
}

