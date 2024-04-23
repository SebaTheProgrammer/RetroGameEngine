#include "AnimatedTextureComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "GameTime.h"

dae::AnimatedTextureComponent::AnimatedTextureComponent( GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int rows, int columns, int level, float frameTime )
:
	BaseComponent( parentGameObject )
	, m_pTexture( texture )
	, m_Rows( rows )
	, m_Columns( columns )
	, m_FrameTime( frameTime )
	, m_CurrentRow( 0 )
	, m_CurrentColumn( level )
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
	if ( m_pTexture ) {
		// Update position based on the local and world transform
		const auto& pos = m_LocalTransform.GetPosition() + GetOwner()->GetWorldTransform().GetPosition();
		m_X = pos.x;
		m_Y = pos.y;

		// Check frame time to avoid division by zero and incorrect accumulation
		if ( m_FrameTime > 0.0f ) {
			m_AccumulatedTime += GameTime::GetInstance().GetDeltaTime();

			if ( m_AccumulatedTime >= m_FrameTime ) {
				// Reset accumulated time
				m_AccumulatedTime -= m_FrameTime;

				// Update column and handle wrap-around
				m_CurrentColumn++;
				if ( m_CurrentColumn >= m_ActiveColumns ) {
					m_CurrentColumn = 0;
					m_CurrentRow++;

					// Update row and handle wrap-around
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

	// Render the texture using the calculated source rect
	dae::Renderer::GetInstance().RenderTexture( *m_pTexture, m_X, m_Y, float( wichlevelIndexHeight ) * m_Scale, float( wichlevelIndexWidth ) * m_Scale, &sourceRect );
}

void dae::AnimatedTextureComponent::NextFrame()
{
	m_CurrentRow++;

	if ( m_CurrentRow >= m_ActiveRows ) 
	{
		m_CurrentRow = 0;
	}
}
