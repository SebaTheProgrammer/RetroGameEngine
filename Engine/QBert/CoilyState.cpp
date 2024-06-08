#include "CoilyState.h"
#include "Coily.h"

CoilyState::CoilyState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily )
	: BaseState(),
	m_pTextureCoily( textureCoily )
{
}

