#include "CoilyStateHandeler.h"

CoilyStateHandeler::CoilyStateHandeler( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily )
{
	m_pCoilyState = std::make_shared<CoilyState>( textureCoily );
	m_pEggState = std::make_shared<EggState>( textureCoily );
}

CoilyStateHandeler::~CoilyStateHandeler()
{
}

void CoilyStateHandeler::SetState( int state )
{
	if ( state == 0 )
	{
		m_pEggState->OnEnter();
	}
	else
	{
		m_pCoilyState->OnEnter();
	}
}
