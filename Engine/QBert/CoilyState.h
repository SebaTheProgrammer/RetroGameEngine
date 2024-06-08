#pragma once
#include "BaseState.h"
#include <AnimatedTextureComponent.h>

class CoilyState : public dae::BaseState
{
public:
	explicit CoilyState( std::shared_ptr<dae::AnimatedTextureComponent> textureCoily );

	virtual void OnEnter() override {};
	virtual void OnExit() override {};

	virtual void Update() override {};

protected:
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureCoily;
};
