#pragma once
#include "CoilyState.h"
#include "Coily.h"

class SnakeState : CoilyState
{
	public:
	explicit SnakeState(Coily* coily);
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
};

