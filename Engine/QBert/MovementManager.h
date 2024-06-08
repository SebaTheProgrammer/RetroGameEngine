#pragma once
#include <glm/glm.hpp>
#include "SingleMovementComponent.h"

class MovementManager final
{
public:
	static MovementManager& GetInstance()
	{
		static MovementManager instance{};
		return instance;
	}

	struct Movement
	{
		glm::vec2 vector;
		SingleMovementComponent::Direction direction;
	};

	Movement Rightdown{ glm::vec2{ 0.75f, 1.2f }, SingleMovementComponent::Direction::RightDown };
	Movement Leftdown{ glm::vec2{ -0.75f, 1.2f }, SingleMovementComponent::Direction::LeftDown };
	Movement Rightup{ glm::vec2{ 0.75f, -1.2f }, SingleMovementComponent::Direction::RightUp };
	Movement Leftup{ glm::vec2{ -0.75f, -1.2f }, SingleMovementComponent::Direction::LeftUp };

private:
	MovementManager() = default;
};