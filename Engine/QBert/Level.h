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
	Level( dae::GameObject* parentGameObject, int howLongLevel, int level, int maxLevels,
		std::shared_ptr<dae::Texture2D> idle, std::shared_ptr<dae::Texture2D> backface, int qbertlives );
	~Level() {};

	void Update() override;
	void Render() const override;

	void GameOver( int score );
	void WinGame( int score );

	enum class LevelState
	{
		Begin,
		GameOver,
		Win,
		Normal
	};
private:
	LevelState m_CurrentState = LevelState::Begin;

	//Level
	const int m_MAX_LEVEL = 5;
	std::shared_ptr<dae::GameObject> m_BeginScreenObject;

	std::shared_ptr<dae::GameObject> m_pGameOverObject;
	std::shared_ptr<dae::GameObject> m_pWinObject;

	//Player
	std::shared_ptr<dae::GameObject> m_QbertGameObject;

	//Enemies
	std::vector<std::shared_ptr<dae::GameObject>> m_CoilyGameObject;

	float m_BeginTimer{ 0 };
	const float m_BeginTime{ 3 };
	int m_LevelSize;
};