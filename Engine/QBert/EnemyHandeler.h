#pragma once
#include <vector>
#include <memory>
#include "Coily.h"

class EnemyHandeler
{
public:
	EnemyHandeler();
	~EnemyHandeler();
	EnemyHandeler( const EnemyHandeler& other ) = delete;
	EnemyHandeler( EnemyHandeler&& other ) = delete;
	EnemyHandeler& operator=( const EnemyHandeler& other ) = delete;
	EnemyHandeler& operator=( EnemyHandeler&& other ) = delete;

private:
	std::vector<std::shared_ptr<Coily>> m_pCoilies;

};

