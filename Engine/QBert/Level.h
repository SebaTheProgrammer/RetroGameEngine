#pragma once
#include "BaseComponent.h"
#include <TextureComponent.h>
#include "Texture2D.h"

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
	const int m_MAX_LEVEL = 5;
	std::shared_ptr<PyramidCubes > m_pPyramid;

	dae::GameObject* m_QbertGameObject;
	std::vector < std::shared_ptr<QBert>> m_pQberts;

	std::shared_ptr < dae::TextureComponent> m_Background;
};