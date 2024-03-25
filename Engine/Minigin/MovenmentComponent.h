#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "GameObject.h"

namespace dae
{
	class MovenmentComponent final : public BaseComponent
	{
	public:

		MovenmentComponent( GameObject* const parentGameObject, float movementSpeed );

		virtual ~MovenmentComponent() = default;
		MovenmentComponent( const MovenmentComponent& other ) = delete;
		MovenmentComponent( MovenmentComponent&& other ) = delete;
		MovenmentComponent& operator=( const MovenmentComponent& other ) = delete;
		MovenmentComponent& operator=( MovenmentComponent&& other ) = delete;

		void Move( glm::vec2 direction );

	private:

		const float m_MovementSpeed;
	};
}

