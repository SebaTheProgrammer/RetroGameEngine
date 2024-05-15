#include "HealthComponentQbert.h"
#include "GameObject.h"
#include "Observer.h"
#include "QBert.h"
#include "ResourceManager.h"
#include "Renderer.h"

HealthComponentQbert::HealthComponentQbert( dae::GameObject* parentGameObject, int lives) :
	BaseComponent( parentGameObject ), m_Lives( lives ), m_StartLives( lives )
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture( "Heart.png" );
}

void HealthComponentQbert::Update()
{
	if ( m_pTexture )
	{
		const auto& pos = m_LocalTransform.GetPosition() + GetOwner()->GetWorldTransform().GetPosition();
		m_X = pos.x;
		m_Y = pos.y;
	}
}

void HealthComponentQbert::Render() const
{
	if ( m_pTexture )
	{
		for ( float i = 0; i < m_Lives; ++i )
		{
			dae::Renderer::GetInstance().RenderTexture( *m_pTexture, m_X + i * 20, m_Y );
		}
	}
}
