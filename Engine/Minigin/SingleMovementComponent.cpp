#include "SingleMovementComponent.h"
#include "GameTime.h"

dae::SingleMovementComponent::SingleMovementComponent( GameObject* const parentGameObject, float speed, float timeTakenForStep )
	: MovenmentComponent( parentGameObject, speed )
	, m_TimeTakenForStep{ timeTakenForStep }
	, m_Speed{ speed }
{
}

void dae::SingleMovementComponent::SingleMove( glm::vec2 direction )
{
    // Only allow a new movement if there is no movement in progress and the delay has passed
    if ( !m_MovementInProgress && m_MovementDelayTimer < 0.0f )
    {
        // Start a new movement
        m_MovementInProgress = true;

        glm::vec2 totalDistance = direction * m_StepSize;

        glm::vec2 movementDelta = glm::vec2( 0.0f );

        // Calculate the movement delta over the specified time
        while ( m_ElapsedTime < m_TimeTakenForStep )
        {
            float deltaTime = GameTime::GetInstance().GetDeltaTime();

            // Update elapsed time
            m_ElapsedTime += deltaTime;

            // Calculate fraction of time passed
            float fractionTimePassed = m_ElapsedTime / m_TimeTakenForStep;

            // Calculate the proportion of total distance to move based on the fraction of time passed
            movementDelta = totalDistance * fractionTimePassed;

            // Move the component with the calculated delta
            MovenmentComponent::Move( movementDelta );
        }

        // Movement is complete
        m_MovementInProgress = false;

        // Reset elapsed time for next movement
        m_ElapsedTime = 0.0f;

        // Reset the delay timer
        m_MovementDelayTimer = 1.0f;
    }

    // Increment the movement delay timer
    m_MovementDelayTimer -= GameTime::GetInstance().GetDeltaTime();
}

