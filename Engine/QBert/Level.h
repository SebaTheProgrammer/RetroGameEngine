#pragma once
#include "BaseComponent.h"
#include <TextureComponent.h>
class QBert;
class PyramidCubes;

class Level : public dae::BaseComponent
{
public:
	Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level );
	virtual ~Level() = default;

	void Update() override;
	void Render() const override;

private:

	std::shared_ptr<PyramidCubes > m_pPyramid;
	std::vector < std::shared_ptr<QBert>> m_pQberts;

	std::shared_ptr < dae::TextureComponent> m_Background;
};