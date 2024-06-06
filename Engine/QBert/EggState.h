#pragma once
#include "CoilyState.h"

class EggState : CoilyState
{
	public:
	explicit EggState(Coily* coily);
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
};

