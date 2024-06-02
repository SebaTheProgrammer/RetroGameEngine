#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "QBert.h"
#include "GameActor.h"
#include "Observer.h"
#include "GameObject.h"
class Cube;

class PyramidCubes : public dae::BaseComponent, public dae::GameActor
{
public:
	PyramidCubes( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, int size, int wichLevel, int howManuJumpsNeeded);
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
	void ResetIndex1();
	void ResetIndex2();
	void GameOver();
	void WalkedOnCube( SingleMovementComponent::Direction dir, int wichplayer );
	void ReverseCube(int row );

	int GetActiveRow() const { return m_QBert1ColIndex; }
	int GetActiveColumn() const { return m_QBert1RowIndex; }
	int GetActiveRow2() const;
	int GetActiveColumn2() const;

	int GetRowStartIndex( int col ) const;
	int GetRowEndIndex( int col ) const;
	int GetSize() const { return m_Size; }

	std::vector<std::shared_ptr<Cube>> GetCubes() const { return m_pCubes; }

	void KilledEnemy();
	void Player1Hit();
	void Player2Hit();
	void PlayerDied();
	void CoilyDead();
	void RemovePlayer();

	void SetCoop( bool coop ) { m_IsCoop = coop; };

	void SetLeftBottom();
	void SetRightBottom();

private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	int m_Size;
	int m_WhichLevel;
	int m_HowManyJumpsNeeded;

	std::vector<std::shared_ptr<Cube>> m_pCubes;
	std::shared_ptr<Cube> m_EndGoalCube;

	float m_Scale = 1.5f;

	int m_QBert1RowIndex = 0;
	int m_QBert1ColIndex = 1;

	int m_QBert2RowIndex = 0;
	int m_QBert2ColIndex = 1;

	int m_CompletedCubes = 0;

	bool m_CanMove = true;
	bool m_IsCoop = false;
};

