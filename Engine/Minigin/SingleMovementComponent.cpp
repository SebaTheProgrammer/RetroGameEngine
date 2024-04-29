#include "SingleMovementComponent.h"
#include "GameTime.h"
#include "../QBert/QBert.h"
#include <iostream>

SingleMovementComponent::SingleMovementComponent( dae::GameObject* const parentGameObject, float speed, float timeTakenForStep)
	: MovenmentComponent( parentGameObject, speed )
	, m_TimeBetweenSteps{ timeTakenForStep }
	, m_Speed{ speed }
{
}

void SingleMovementComponent::SingleMove( glm::vec2 direction, Direction dir )
{
    if ( m_CanMove ) 
    {
        //This is a simple way to make sure the movement is not interrupted
        //you also need to hold the key to have a old school feel
        if ( !m_MovementInProgress && m_MovementDelayTimer <= 0.0f )
        {
            m_MovementInProgress = true;
            glm::vec2 totalDistance = direction * m_StepSize;
            glm::vec2 movementDelta = glm::vec2( 0.0f );

            while ( m_ElapsedTime < 1.0f )
            {
                float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

                m_ElapsedTime += deltaTime;

                movementDelta = totalDistance * m_ElapsedTime;

                MovenmentComponent::Move( movementDelta );
            }

            m_Direction = dir;

            GetOwner()->GetComponent<QBert>().get()->Moved( m_Direction );

            m_MovementInProgress = false;
            m_ElapsedTime = 0.0f;
            m_MovementDelayTimer = m_TimeBetweenSteps;
        }

        m_MovementDelayTimer -= dae::GameTime::GetInstance().GetDeltaTime();
    }
}

