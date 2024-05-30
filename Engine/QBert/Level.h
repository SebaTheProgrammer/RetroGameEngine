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
	struct allTextures
	{
		std::shared_ptr<dae::Texture2D> m_BgTexture;
		std::shared_ptr<dae::Texture2D> m_CubesTexture;
		std::shared_ptr<dae::Texture2D> m_GameOverTexture;
		std::shared_ptr<dae::Texture2D> m_WinTexture;
		std::shared_ptr<dae::Texture2D> m_BeginTexture;

		std::shared_ptr<dae::Texture2D> m_QbertIdle;
		std::shared_ptr<dae::Texture2D> m_QbertBackfaceIdle;

		std::shared_ptr<dae::Texture2D> m_Coily;
		std::shared_ptr<dae::Texture2D> m_UggWrongWay;
		std::shared_ptr<dae::Texture2D> m_Slick;
		std::shared_ptr<dae::Texture2D> m_Sam;
	};

	Level( dae::GameObject* parentGameObject, int howLongLevel, int level, int howManuJumpsNeeded, int maxLevels,
		allTextures textures, int qbertlives );

	~Level() {};

	void Update() override;
	void Render() const override;

	void GameOver( int score );
	void CompletedLevel();
	void WinGame( int score );
	void RestartLevel();
	void Player1Moved();
	void Player2Moved();
	void SetMultiplayer( bool isMultiplayer );
	void SetVersus( bool isVersus );
	void SinglePlayer();

	void CoilyDied();

	enum class LevelState
	{
		Begin,
		GameOver,
		Win,
		Normal
	};

private:
	allTextures m_Textures;

	LevelState m_CurrentState = LevelState::Begin;

	//Level
	const int m_MAX_LEVEL = 5;
	int m_Level;
	std::shared_ptr<dae::GameObject> m_BeginScreenObject;

	std::shared_ptr<dae::GameObject> m_pGameOverObject;
	std::shared_ptr<dae::GameObject> m_pWinObject;

	//Player
	std::vector < std::shared_ptr<dae::GameObject>> m_QbertGameObject;
	bool m_Player1Moved = false;
	bool m_Player2Moved = false;

	//Enemies
	std::shared_ptr<dae::GameObject> m_EnemyHandeler;
	bool m_HasCoily{ false };
	std::shared_ptr<PyramidCubes> m_pPyramidCubes;
	int m_HowManyEnemies{ 0 };
	int m_MaxScoreEnemies{2};

	float m_Timer{ 0 };
	const float m_BeginTime{ 3.f };
	float m_SpawnEnemyTime{ 6.5f };
	float m_MaxSpawnEnemyTime{ 16.5 };
	int m_LevelSize;

	bool m_IsMultiplayer{ false };
	bool m_IsVersus{ false };

	bool m_StartSound{ true };
};