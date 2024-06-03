#pragma once
#include <vector>
#include <memory>
#include "Coily.h"
#include "BaseComponent.h"
#include "GameActor.h"
#include "Level.h"

class EnemyHandeler : public dae::BaseComponent, public dae::GameActor
{
public:
	EnemyHandeler( dae::GameObject* parentGameObject, PyramidCubes* pyramid, Level::allTextures textures, int maxScoreEnemies, int levelsize );
	~EnemyHandeler();
	EnemyHandeler( const EnemyHandeler& other ) = delete;
	EnemyHandeler( EnemyHandeler&& other ) = delete;
	EnemyHandeler& operator=( const EnemyHandeler& other ) = delete;
	EnemyHandeler& operator=( EnemyHandeler&& other ) = delete;

	void Update() override;
	void Render() const override;

	void SpawnCoily();
	void SpawnSlick();
	void SpawnSam();
	void SpawnUggWrongway();
	void SpawnEnemies();

	void SetCanMove( bool move );
	void SetHasCoily( bool hasCoily );
	void SetVersus( bool isVersus ) { m_IsVersus = isVersus; }
	void Clear();

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_EnemiesGameObjects;
	std::shared_ptr<dae::GameObject> m_pCoily;

	Level::allTextures m_Textures;
	PyramidCubes* m_pPyramid;

	int m_LevelSize;
	int m_HowManyEnemies{ 0 };
	int m_MaxScoreEnemies;

	bool m_HasCoily{ false };
	bool m_IsVersus{ false };
};

