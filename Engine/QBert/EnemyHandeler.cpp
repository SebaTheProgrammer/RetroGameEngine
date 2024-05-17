#include "EnemyHandeler.h"
#include "Coily.h"
#include <memory>

EnemyHandeler::EnemyHandeler( dae::GameObject* parentGameObject):
	BaseComponent( parentGameObject )
{
}

EnemyHandeler::~EnemyHandeler()
{
}

void EnemyHandeler::Update()
{
	for ( int i = 0; i < m_pCoilies.size(); ++i )
	{
		m_pCoilies[i]->Update();
	}
}

void EnemyHandeler::Render() const
{
	for ( int i = 0; i < m_pCoilies.size(); ++i )
	{
		m_pCoilies[i]->Render();
	}
}

void EnemyHandeler::SpawnCoily( const int row, const int col )
{
	//m_pCoilies.push_back( std::make_shared<Coily>( GetOwner(), m_pTextureIdleEgg, m_pTextureJumpEgg, m_pTextureIdleSnake, m_pTextureJumpSnake ) );
	m_pCoilies[m_pCoilies.size() - 1]->SetPyramidPosition( row, col );
}

void EnemyHandeler::DeleteCoily( const int row, const int col )
{
	for ( int i = 0; i < m_pCoilies.size(); ++i )
	{
		if ( m_pCoilies[ i ]->GetRow() == row && m_pCoilies[ i ]->GetCol() == col )
		{
			m_pCoilies.erase( m_pCoilies.begin() + i );
			break;
		}
	}
}

void EnemyHandeler::CheckEnemy( const int row, const int col )
{
	for ( int i = 0; i < m_pCoilies.size(); ++i )
	{
		if ( m_pCoilies[ i ]->GetRow() == row && m_pCoilies[ i ]->GetCol() == col )
		{
			NotifyObservers( dae::EventType::PLAYER_HIT, GetOwner() );
			break;
		}
	}
}
