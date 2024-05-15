#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"

class QBert;

class HealthComponentQbert final : public dae::BaseComponent
{
public:
	HealthComponentQbert( dae::GameObject* parentGameObject, int lives);
	virtual ~HealthComponentQbert() = default;

	HealthComponentQbert( const HealthComponentQbert& other ) = delete;
	HealthComponentQbert( HealthComponentQbert&& other ) = delete;
	HealthComponentQbert& operator=( const HealthComponentQbert& other ) = delete;
	HealthComponentQbert& operator=( HealthComponentQbert&& other ) = delete;

	virtual void Update() override;
	virtual void Render() const override;

	void SetLives( int lives ){ m_Lives = lives; m_NeedsUpdate = true;}

private:
	int m_Lives;
	int m_StartLives;
	bool m_NeedsUpdate{ false };

	std::shared_ptr<dae::Texture2D> m_pTexture;

	float m_X = 0;
	float m_Y = 0;
};