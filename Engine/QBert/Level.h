#pragma once
#include "BaseComponent.h"
#include <TextureComponent.h>
#include "Texture2D.h"
#include "TextComponent.h"

class QBert;
class PyramidCubes;

class Level : public dae::BaseComponent
{
public:
	Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level );
	~Level();

	void Update() override;
	void Render() const override;

private:
	//Level
	const int m_MAX_LEVEL = 5;

	//Player
	dae::GameObject* m_QbertGameObject;

};