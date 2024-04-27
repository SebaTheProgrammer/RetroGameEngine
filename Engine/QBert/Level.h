#pragma once
#include "BaseComponent.h"
#include <TextureComponent.h>
#include "Texture2D.h"
#include "PlayerStats.h"
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
	std::shared_ptr<PyramidCubes > m_pPyramid;
	std::shared_ptr < dae::TextureComponent> m_Background;

	//Players
	dae::GameObject* m_QbertGameObject;

	//Stats
	std::shared_ptr<PlayerStats> m_pStats;
	std::shared_ptr < dae::TextComponent> m_pHealthDisplay;


};