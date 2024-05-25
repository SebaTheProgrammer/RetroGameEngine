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
	void CompletedLevel();
	void WinGame( int score );

	enum class LevelState
	{
		Begin,
		GameOver,
		Win,
		Normal
	};
	void PlayerMoved();
private:
	void SpawnSlickSam();
	void SpawnCoily();

	LevelState m_CurrentState = LevelState::Begin;

	//Level
	const int m_MAX_LEVEL = 5;
	int m_Level;
	std::shared_ptr<dae::GameObject> m_BeginScreenObject;

	std::shared_ptr<dae::GameObject> m_pGameOverObject;
	std::shared_ptr<dae::GameObject> m_pWinObject;

	//Player
	std::shared_ptr<dae::GameObject> m_QbertGameObject;
	bool m_PlayerMoved = false;

	//Enemies
	std::vector<std::shared_ptr<dae::GameObject>> m_EnemiesGameObjects;
	std::shared_ptr<PyramidCubes> m_pPyramidCubes;
	int m_HowManyEnemies{ 0 };
	int m_MaxEnemies{};

	float m_Timer{ 0 };
	const float m_BeginTime{ 3.f };
	const float m_SpawnEnemyTime{ 16.5f };
	int m_LevelSize;
};