#pragma once
#include "CoilyState.h"
#include "Coily.h"

class SnakeState : CoilyState
{
	public:
	explicit SnakeState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily );
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override {};
};

