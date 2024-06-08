#include "Cube.h"
#include "Renderer.h"
#include <iostream>

Cube::Cube( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int level, int howManuJumpsNeeded )
	: BaseComponent( parentGameObject ), m_Level( level ), m_HowManyJumpsNeeded( howManuJumpsNeeded )
{
																							//hardcoded values bc png is 3x6
	m_pTexture = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, texture, scale, 3, 6, m_Level, 0.0f );
	GetOwner()->AddComponent( m_pTexture );

	Reset();
}

void Cube::Update()
{
	m_pTexture->Update();
}

void Cube::Render() const
{
	m_pTexture->Render();
}

void Cube::SetLocalPosition( float x, float y)
{
	m_pTexture->SetLocalPosition( x, y );
}

void Cube::Won()
{
	m_pTexture->Animate( m_WinFrameTime );
}

void Cube::LandedOnThisCube()
{
	if( m_Completed ) return;
	if ( m_CurrentFrame < m_HowManyJumpsNeeded )
	{
		m_pTexture->NextFrame();
		++m_CurrentFrame;
	}
	if( m_CurrentFrame == m_HowManyJumpsNeeded )
	{
		NotifyObservers( dae::EventType::NEW_CUBE_COMPLETED, GetOwner() );
		m_Completed = true;
	}
}

void Cube::ReverseOne()
{
	if ( m_CurrentFrame > 0 || m_CurrentFrame >=0 && m_Completed == true)
	{
		m_pTexture->PreviousFrame();
		--m_CurrentFrame;
		m_Completed = false;
	}
}

void Cube::Reset()
{
	m_pTexture->Reset();
	m_pTexture->SetCurrentColumn( m_Level );
	m_Completed = false;
	m_CurrentFrame = 0;
}

void Cube::CompletedCube()
{
	while ( m_CurrentFrame < m_HowManyJumpsNeeded )
	{
		m_pTexture->NextFrame();
		++m_CurrentFrame;
	}
	if ( m_CurrentFrame == m_HowManyJumpsNeeded )
	{
		m_Completed = true;
	}
}
