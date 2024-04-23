#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include <AnimatedTextureComponent.h>

class QBert : public dae::BaseComponent
{
	public:
	QBert( dae::GameObject* parentGameObject, bool keyboardinput);
	virtual ~QBert() = default;

	void Update() override;
	void Render() const override;

private:
	bool m_KeyBoardInput;
	//std::shared_ptr<dae::AnimatedTextureComponent> m_pTexture;

	float m_X;
	float m_Y;
};