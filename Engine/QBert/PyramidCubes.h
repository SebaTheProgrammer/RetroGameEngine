#pragma once
#include "BaseComponent.h"
#include <GameObject.h>
#include "Observer.h"
#include "QBert.h"

class Cube;

class PyramidCubes : public dae::BaseComponent, public dae::GameActor
{
public:
	PyramidCubes( dae::GameObject* parentGameObject, int size, int wichLevel);
	virtual ~PyramidCubes()= default;

	PyramidCubes( const PyramidCubes& other ) = delete;
	PyramidCubes( PyramidCubes&& other ) = delete;
	PyramidCubes& operator=( const PyramidCubes& other ) = delete;
	PyramidCubes& operator=( PyramidCubes&& other ) = delete;

	void SetScaleSize( int size ) { m_Size = size; SetLevel( m_WhichLevel ); }
	void SetWhichLevel(int whichLevel){ m_WhichLevel = whichLevel; }

	void Update() override;
	void Render() const override;

	void SetLevel( const int level);
	void SetScale( float scale ) { m_Scale = scale; };

	void CompleteLevel();
	void ResetLevel();
	void ResetIndex();
	void GameOver();
	void WalkedOnCube( SingleMovementComponent::Direction dir);

	int GetActiveRow() const { return m_QBertColIndex; }
	int GetActiveColumn() const { return m_QBertRowIndex; }

private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	int m_Size;
	int m_WhichLevel;

	std::vector<std::shared_ptr<Cube>> m_pCubes;

	float m_Scale = 1.5f;

	int m_QBertRowIndex = 0;
	int m_QBertColIndex = 1;

	int m_CompletedCubes = 0;

	bool m_CanMove = true;
};

