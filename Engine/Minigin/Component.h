#pragma once
#include <string>

namespace dae
{
	class GameObject;

	class Component
	{
	public:

		Component( GameObject* gameObject ) { m_pGameObject = gameObject; }
		virtual ~Component() = default;

		Component( const Component& other ) = delete;
		Component( Component&& other ) = delete;
		Component& operator=( const Component& other ) = delete;
		Component& operator=( Component&& other ) = delete;

		virtual void Update();
		virtual void Render() const;

	private:

		GameObject* m_pGameObject = nullptr;
	};
}

