#include "BaseComponent.h"

void dae::BaseComponent::SetParent( std::shared_ptr<GameObject> parent )
{
	if ( parent != nullptr ) 
	{
		m_pGameObject = parent;
	}
}
