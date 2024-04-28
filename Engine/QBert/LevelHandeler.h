#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"

class QBert;

class LevelHandeler final : public dae::BaseComponent, public dae::Observer
{
	public:
	LevelHandeler( dae::GameObject* const parentGameObject, int lives );
	~LevelHandeler();

	void Update() override;
	void Notify( dae::EventType event, dae::GameObject* gameObj ) override;

	void SetLives(int lives);
	void SetScore(int score);

	int GetLives() const;
	int GetScore() const;

private:
	bool m_NeedsUpdate;
	int m_Lives;
	int m_Score;

	QBert* m_pQbert;
};

