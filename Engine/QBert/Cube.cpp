#include "Cube.h"
#include "Renderer.h"

Cube::Cube( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int level )
	: BaseComponent( parentGameObject ), m_Level( level )
{
																							//hardcoded values bc png is 3x6
	m_pTexture = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, texture, scale, 3, 6, level, 0.0f );
	GetOwner()->AddComponent( m_pTexture );
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
						//level 1 == 0
	if ( m_CurrentFrame < m_Level+1 ) 
	{
		m_pTexture->NextFrame();
		++m_CurrentFrame;
	}
	else
	{
		m_Completed = true;
	}
}