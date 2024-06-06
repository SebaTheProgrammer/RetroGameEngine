#include "FloatingDisc.h"
#include <iostream>
#include <cmath>
#include "GameTime.h"
#include "Utilities.h"

FloatingDisc::FloatingDisc( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureDisc, int levelSize, int wichlevel, bool isLeftDisc )
	: BaseComponent( parentGameObject )
	, m_LevelSize( levelSize )
	, m_IsLeftDisc( isLeftDisc )
{
	m_pTextureDisc = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureDisc, 2.0f, 1, 30, 1, m_FrameTime );
	m_pTextureDisc->SetMinColumns( wichlevel * 5 - 5);
	m_pTextureDisc->SetMaxColumns( wichlevel * 5);
	m_pTextureDisc->SetCurrentColumn( wichlevel * 5 - 5 );

	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_pSingleMovenment->SetCanMove( true );
	m_pSingleMovenment->SetPlayAudio( false );
}

glm::vec2 Lerp( const glm::vec2& start, const glm::vec2& end, float t )
{
	return start + t * ( end - start );
}

void FloatingDisc::Update()
{
	if ( m_IsAlive ) {
		m_pSingleMovenment->Update();

		ResetPosition();

		if ( m_pTextureDisc )
		{
			m_pTextureDisc->Update();
		}

		if ( m_FloatingToTop ) 
		{
			glm::vec2 currentPosition = GetOwner()->GetLocalTransform().GetPosition();

			glm::vec2 direction = m_StartPos - currentPosition;
			float distance = glm::length( direction );

			if ( distance > 0.0f ) 
			{
				direction /= distance;

				float moveDistance = m_Speed * dae::GameTime::GetInstance().GetDeltaTime();

				glm::vec2 newPosition;
				if ( moveDistance < distance ) {
					newPosition = currentPosition + direction * moveDistance;
				}
				else {
					newPosition = m_StartPos;
					m_FloatingToTop = false;
					m_IsAlive = false;

					NotifyObservers( dae::EventType::DISC_FLOAT_TO_TOP, GetOwner() );
				}

				GetOwner()->SetLocalTransform( newPosition );
			}
		}
	}
}

void FloatingDisc::Render() const
{
	if ( m_IsAlive ) {
		if ( m_pTextureDisc )
		{
			m_pTextureDisc->Render();
		}
	}
}

void FloatingDisc::FloatToTop()
{
	m_FloatingToTop = true;
}

glm::vec2 FloatingDisc::GetRowCol() const
{
	if ( m_IsAlive ) {
		return glm::vec2( m_Row, m_Col );
	}
	else {
		return glm::vec2( -1, -1 );
	}
}

void FloatingDisc::ResetPosition()
{
	if ( !m_SettetStartPos ) 
	{
		m_Row = 0;
		m_Col = 0;

		m_StartPos = GetOwner()->GetLocalTransform().GetPosition();
		m_StartPos.x+=m_Offset.x;
		m_StartPos.y-=m_Offset.y;

		m_IsLeftDisc = ( rand() % 2 == 0 );

		if ( m_IsLeftDisc )
		{
			m_Direction = glm::vec2{ -0.75f, 1.2f };
		}
		else
		{
			m_Direction = glm::vec2{ 0.75f, 1.2f };
		}

		for ( int i = 0; i < rand() % ( m_LevelSize - 2 ) + 2; ++i )
		{
			if ( m_IsLeftDisc == 1 )
			{
				m_pSingleMovenment->SingleMove( m_Direction, SingleMovementComponent::Direction::LeftDown, true );
				m_Row += 1;
				m_Col = 0;
			}
			else
			{
				m_pSingleMovenment->SingleMove( m_Direction, SingleMovementComponent::Direction::RightDown, true );
				m_Row += 1;
				m_Col = 1;
			}
		}
		m_SettetStartPos = true;

		GetOwner()->AddLocalTransform( glm::vec3{ m_Offset.x, m_Offset.y, 0.0f } );
	}
}
