#include "FloatingDisc.h"

FloatingDisc::FloatingDisc( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureDisc, int levelSize, bool isLeftDisc )
	: BaseComponent( parentGameObject )
	, m_LevelSize( levelSize )
	, m_IsLeftDisc( isLeftDisc )
{
	m_pTextureDisc = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureDisc, 1, 1, 1, m_FrameTime );
	m_pSingleMovenment = std::make_shared<SingleMovementComponent>( parentGameObject, levelSize );
}

void FloatingDisc::Update()
{
	if ( m_CanMove )
	{
		m_pSingleMovenment->Update();
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

void FloatingDisc::SetPyramidPosition( const int x, const int y )
{
	m_Row = x;
	m_Col = y;
}
