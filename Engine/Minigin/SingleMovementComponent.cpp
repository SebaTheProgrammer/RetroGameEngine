#include "SingleMovementComponent.h"
#include "GameTime.h"
#include "../QBert/QBert.h"
#include <iostream>
#include "../QBert/Coily.h"
#include "../QBert/SlickSam.h"
#include "../QBert/UggWrongWay.h"
#include <ServiceLocator.h>

SingleMovementComponent::SingleMovementComponent( dae::GameObject* const parentGameObject, float speed, float timeTakenForStep, bool instantJump)
	: MovenmentComponent( parentGameObject, speed )
	, m_TimeBetweenSteps{ timeTakenForStep }
	, m_Speed{ speed }
    , m_InstantJump{ instantJump }
{
}

void SingleMovementComponent::SingleMove( glm::vec2 direction, Direction dir, bool byPC )
{
    if ( m_CanMove )
    {
        if ( m_InstantJump && byPC )
        {
            auto& ss = dae::ServiceLocator::GetSoundSystem();
            ss.AddSound( "Jump", "Sounds/Jump.wav" );
            ss.Play( ss.GetSoundId( "Jump" ), 25 );

            m_Direction=dir;
            glm::vec2 totalDistance = direction * m_StepSize*30.f;
            MovenmentComponent::Move( totalDistance );

            //Should make a base class for the enemies
            if ( GetOwner()->GetComponent<Coily>() )
            {
                GetOwner()->GetComponent<Coily>().get()->Moved( m_Direction );
            }
            if ( GetOwner()->GetComponent<SlickSam>() )
            {
                GetOwner()->GetComponent<SlickSam>().get()->Moved( m_Direction );
            }
            if ( GetOwner()->GetComponent<UggWrongWay>() )
            {
				GetOwner()->GetComponent<UggWrongWay>().get()->Moved( m_Direction );
			}
            return;
        }

        //This is a simple way to make sure the movement is not interrupted
        //you also need to hold the key to have a old school feel
        else if ( !m_MovementInProgress && m_MovementDelayTimer <= 0.0f && m_HasControl )
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

            m_MovementInProgress = false;
            m_ElapsedTime = 0.0f;
            m_MovementDelayTimer = m_TimeBetweenSteps;

            m_Direction = dir;

            if ( GetOwner()->GetComponent<QBert>() )
            {
                GetOwner()->GetComponent<QBert>().get()->Moved( m_Direction );
            }
            if ( GetOwner()->GetComponent<Coily>() )
            {
                GetOwner()->GetComponent<Coily>().get()->Moved( m_Direction );
            }
        }

        m_MovementDelayTimer -= dae::GameTime::GetInstance().GetDeltaTime();
    }
}

