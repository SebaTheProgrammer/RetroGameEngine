#pragma once
#include "CoilyState.h"

class EggState : CoilyState
{
	public:
	explicit EggState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily);
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override {};
};

