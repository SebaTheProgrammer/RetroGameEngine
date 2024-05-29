#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"
#include "TextureComponent.h"

class QBert;

class LevelHandeler final : public dae::BaseComponent, public dae::Observer
{
public:
	LevelHandeler( dae::GameObject* parentGameObject, int& lives, int maxLevels );
	~LevelHandeler() {};

	void Update() override;
	void Notify( dae::EventType event, dae::GameObject* gameObj ) override;

	void SetLives( int lives );
	void SetScore( int score );

	int GetLives1() const;
	int GetLives2() const;
	int GetScore() const;

private:
	bool m_NeedsUpdate{ false };
	int m_Lives1;
	int m_Lives2;
	int m_StartLives;
	int m_Score;
	int m_MaxLevels;

	std::shared_ptr<QBert> m_pQbert;
	std::shared_ptr<QBert> m_pQbert2;

	bool m_CompletedLevel = false;

	float m_EndTimer = 0.0f;
	const float m_EndTimeChangeLevel = 4.0f;

	void ChangeLevel();
	void ResetLevel();
};

