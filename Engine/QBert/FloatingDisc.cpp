#include "FloatingDisc.h"
#include <iostream>

FloatingDisc::FloatingDisc( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureDisc, int levelSize, bool isLeftDisc )
	: BaseComponent( parentGameObject )
	, m_LevelSize( levelSize )
	, m_IsLeftDisc( isLeftDisc )
{
	m_pTextureDisc = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureDisc, 2.0f, 1, 30, 1, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, m_Speed, m_SpeedBetweenSteps, true );
	m_pSingleMovenment->SetCanMove( true );
	m_pSingleMovenment->SetPlayAudio( false );
}

void FloatingDisc::Update()
{
	m_pSingleMovenment->Update();

	ResetPosition();

	if ( m_CanMove )
	{
		FloatToTop();
	}

	if ( m_pTextureDisc )
	{
		m_pTextureDisc->Update();
	}

}

void FloatingDisc::Render() const
{
	if ( m_pTextureDisc )
	{
		m_pTextureDisc->Render();
	}
}

void FloatingDisc::FloatToTop()
{
}

void FloatingDisc::SetPyramidPosition( const int x, const int y )
{
	m_Row = x;
	m_Col = y;

	glm::vec2 totalDistance = m_Direction * m_StepSize * 30.f;
}

void FloatingDisc::ResetPosition()
{
	if ( !m_SettetStartPos ) {
		m_Row = 0;
		m_Col = 0;

		rand() % 2 == 0 ? m_IsLeftDisc = true : m_IsLeftDisc = false;

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

		std::cout<<m_Row<<" "<<m_Col<<std::endl;
	}
}

int FloatingDisc::GetRowStartIndex( int col ) const
{
	return ( ( col - 1 ) * ( col ) ) / 2;
}

int FloatingDisc::GetRowEndIndex( int col ) const
{
	return  GetRowStartIndex( col ) + col - 1;
}
