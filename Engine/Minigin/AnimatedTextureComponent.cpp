#include "AnimatedTextureComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "GameTime.h"

dae::AnimatedTextureComponent::AnimatedTextureComponent( GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int rows, int columns, int currentColumn, float frameTime )
:
	BaseComponent( parentGameObject )
	, m_pTexture( texture )
	, m_Rows( rows )
	, m_Columns( columns )
	, m_FrameTime( frameTime )
	, m_CurrentRow( 0 )
	, m_CurrentColumn( currentColumn )
	, m_AccumulatedTime( 0 )
	, m_X( 0 )
	, m_Y( 0 )
	, m_Scale( scale )
	, m_ActiveRows( rows )
	, m_ActiveColumns( columns )
{
}

void dae::AnimatedTextureComponent::Update()
{
	if ( m_pTexture ) 
	{
		const auto& pos = m_LocalTransform.GetPosition() + GetOwner()->GetWorldTransform().GetPosition();
		m_X = pos.x;
		m_Y = pos.y;

		if ( m_FrameTime > 0.0f ) {
			m_AccumulatedTime += GameTime::GetInstance().GetDeltaTime();

			if ( m_AccumulatedTime >= m_FrameTime ) 
			{
				m_AccumulatedTime -= m_FrameTime;

				m_CurrentColumn++;
				if ( m_CurrentColumn >= m_ActiveColumns ) {
					m_CurrentColumn = 0;
					m_CurrentRow++;

					if ( m_CurrentRow >= m_ActiveRows ) {
						m_CurrentRow = 0;
					}
				}
			}
		}
	}
}

void dae::AnimatedTextureComponent::Render() const
{
	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture( m_pTexture->GetSDLTexture(), nullptr, nullptr, &textureWidth, &textureHeight );

	int wichlevelIndexWidth = textureWidth / m_Columns;
	int wichlevelIndexHeight = textureHeight / m_Rows;

	// Create the source rect
	SDL_Rect sourceRect{};
	sourceRect.x = wichlevelIndexWidth * m_CurrentColumn;
	sourceRect.y = wichlevelIndexHeight * m_CurrentRow;
	sourceRect.w = wichlevelIndexWidth;
	sourceRect.h = wichlevelIndexHeight;

	//mirror
	if ( m_Mirror ) 
	{
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		dae::Renderer::GetInstance().RenderTexture( *m_pTexture, m_X, m_Y, float( wichlevelIndexHeight ) * m_Scale, float( wichlevelIndexWidth ) * m_Scale, &sourceRect, flip );
	}
	else 
	{
		dae::Renderer::GetInstance().RenderTexture( *m_pTexture, m_X, m_Y, float( wichlevelIndexHeight ) * m_Scale, float( wichlevelIndexWidth ) * m_Scale, &sourceRect );
	}
}

void dae::AnimatedTextureComponent::NextFrame()
{
	m_CurrentRow++;

	if ( m_CurrentRow >= m_ActiveRows ) 
	{
		m_CurrentRow = 0;
	}
}
