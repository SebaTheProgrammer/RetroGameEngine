#pragma once
#include "CoilyState.h"
#include "EggState.h"

class CoilyStateHandeler
{
public:
	CoilyStateHandeler( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily );
	~CoilyStateHandeler();

	void SetState( int state );

private:
	std::shared_ptr <CoilyState> m_pCoilyState;
	std::shared_ptr <EggState> m_pEggState;
};

