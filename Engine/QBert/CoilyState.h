#pragma once
#include "BaseState.h"
#include "Coily.h"

class CoilyState : public dae::BaseState
{
public:
	explicit CoilyState(Coily* coily);

	virtual void OnEnter() override {};
	virtual void OnExit() override {};

	virtual void Update() override {};

	Coily* GetCoily() const { return m_pCoily; }

protected:
	Coily* m_pCoily;
};
