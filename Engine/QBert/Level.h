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
	Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level, 
		std::shared_ptr<dae::Texture2D> idle, std::shared_ptr<dae::Texture2D> backface, int qbertlives );
	~Level() {};

	void Update() override;
	void Render() const override;

private:
	//Level
	const int m_MAX_LEVEL = 5;
	std::shared_ptr<dae::GameObject> m_BeginScreenObject;

	//Pyramid
	std::shared_ptr<dae::GameObject> m_PyramidGameObject;

	//Player
	std::shared_ptr<dae::GameObject> m_QbertGameObject;

	bool m_Begin{ true };
	float m_BeginTimer{ 0 };
	const float m_BeginTime{ 3 };

};