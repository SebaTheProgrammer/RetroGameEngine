#pragma once
#include <vector>
#include <memory>
#include "Coily.h"
#include "BaseComponent.h"
#include "GameActor.h"

class EnemyHandeler : public dae::BaseComponent, public dae::GameActor
{
public:
	EnemyHandeler( dae::GameObject* parentGameObject);
	~EnemyHandeler();
	EnemyHandeler( const EnemyHandeler& other ) = delete;
	EnemyHandeler( EnemyHandeler&& other ) = delete;
	EnemyHandeler& operator=( const EnemyHandeler& other ) = delete;
	EnemyHandeler& operator=( EnemyHandeler&& other ) = delete;

	void Update() override;
	void Render() const override;

	void SpawnCoily( const int row, const int col);

	void DeleteCoily( const int row, const int col );

	void CheckEnemy( const int row, const int col );

private:
	std::vector<std::shared_ptr<Coily>> m_pCoilies;

	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleEgg;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJumpEgg;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureIdleSnake;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureJumpSnake;

};

