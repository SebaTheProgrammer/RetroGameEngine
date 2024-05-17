#include "Coily.h"

Coily::Coily( dae::GameObject* parentGameObject, 
	std::shared_ptr<dae::Texture2D> textureIdleEgg, std::shared_ptr<dae::Texture2D> textureJumpEgg, 
	std::shared_ptr<dae::Texture2D> textureIdleSnake, std::shared_ptr<dae::Texture2D> textureJumpSnake ):
	BaseComponent( parentGameObject )
{																										//Hardcoded values for the animation
	m_pTextureIdleEgg = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleEgg, 1, 1, 1, 1, m_FrameTime );
	m_pTextureJumpEgg = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJumpEgg, 1, 1, 1, 1, m_FrameTime );
	m_pTextureIdleSnake = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureIdleSnake, 1, 1, 1, 1, m_FrameTime );
	m_pTextureJumpSnake = std::make_shared<dae::AnimatedTextureComponent>( parentGameObject, textureJumpSnake, 1, 1, 1, 1, m_FrameTime );
}

void Coily::Update()
{
}

void Coily::Render() const
{
}

void Coily::SetAnimationState( AnimationState state )
{

}
