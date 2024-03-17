#include "MovenmentComponent.h"
#include "GameTime.h"

dae::MovenmentComponent::MovenmentComponent( GameObject* const parentGameObject, float movementSpeed )
	: BaseComponent( parentGameObject )
	, m_MovementSpeed{ movementSpeed }
{

}

void dae::MovenmentComponent::Move( glm::vec2 direction )
{
	glm::vec2 addedPosition{ direction * m_MovementSpeed * dae::GameTime::GetInstance().GetDeltaTime() };

	GetOwner()->AddLocalTransform( Transform{ addedPosition } );
}
