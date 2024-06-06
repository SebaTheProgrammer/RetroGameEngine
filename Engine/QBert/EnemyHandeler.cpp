#include "EnemyHandeler.h"
#include "Coily.h"
#include <memory>
#include "SlickSam.h"
#include "UggWrongWay.h"
#include "Level.h"
#include "Utilities.h"

EnemyHandeler::EnemyHandeler( dae::GameObject* parentGameObject, PyramidCubes* pyramid, Level::allTextures textures, int maxScoreEnemies, int levelsize ):
	BaseComponent( parentGameObject ), m_pPyramid( pyramid ), m_MaxScoreEnemies( maxScoreEnemies )
{
	m_Textures = textures;
	m_LevelSize = levelsize;
}

EnemyHandeler::~EnemyHandeler()
{
}

void EnemyHandeler::Update()
{
	for ( auto enemy : m_EnemiesGameObjects )
	{
		if ( enemy != nullptr ) 
		{
			if ( enemy->GetComponent<SlickSam>() )
			{
				if ( enemy->GetComponent<SlickSam>()->IsAlive() )
				{
					enemy->Update();
				}
			}
			else if ( enemy->GetComponent<UggWrongWay>() )
			{
				if ( enemy->GetComponent<UggWrongWay>()->IsAlive() )
				{
					enemy->Update();
				}
			}
		}
	}

	if ( m_pCoily != nullptr ) {
		m_pCoily->Update();
	}
}

void EnemyHandeler::Render() const
{
	for ( auto enemy : m_EnemiesGameObjects )
	{
		if ( enemy != nullptr ) {
			enemy->Render();
		}
	}
	if ( m_pCoily != nullptr ) {
		m_pCoily->Render();
	}
}

void EnemyHandeler::SpawnCoily()
{
	m_HasCoily = true;
	m_pCoily = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
	auto coily = std::make_shared<Coily>( m_pCoily.get(), m_Textures.m_Coily, m_LevelSize, m_pPyramid, m_IsVersus );
	m_pCoily->AddComponent( coily );
	m_pCoily->SetLocalTransform( { 300, 110 } );
}

void EnemyHandeler::SpawnSlick()
{
	m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
	auto slick = std::make_shared<SlickSam>
		( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), m_Textures.m_Slick, m_LevelSize, m_pPyramid );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( slick );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 90 } );
}

void EnemyHandeler::SpawnSam()
{
	m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
	auto sam = std::make_shared<SlickSam>( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(), m_Textures.m_Sam, m_LevelSize, m_pPyramid );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( sam );
	m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 300, 90 } );
}

void EnemyHandeler::SpawnUggWrongway()
{
	if ( m_pPyramid->GetActiveRow() != GetRowStartIndex( m_pPyramid->GetSize() ) &&
		m_pPyramid->GetActiveRow() != GetRowEndIndex( m_pPyramid->GetSize() ) )
	{
		m_EnemiesGameObjects.push_back( std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() ) );
		m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ] = std::make_shared<dae::GameObject>( GetOwner()->GetSceneIndex() );
		auto uggWrongWay = std::make_shared<UggWrongWay>( m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ].get(),
			m_Textures.m_UggWrongWay, m_LevelSize, m_pPyramid );
		m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->AddComponent( uggWrongWay );
		m_EnemiesGameObjects[ m_EnemiesGameObjects.size() - 1 ]->SetLocalTransform( { 310, 120 } );
	}
}

void EnemyHandeler::SpawnEnemies()
{
	if ( !m_HasCoily ) 
	{
		SpawnCoily();
	}
	else {
		if ( m_HowManyEnemies < m_MaxScoreEnemies )
		{
			if ( m_pPyramid->GetActiveRow() != 0 )
			{
				bool randomPoints = rand() % 2;
				if ( randomPoints )
				{
					++m_HowManyEnemies;

					bool random = rand() % 2;
					if ( random )
					{
						SpawnSlick();
					}
					else
					{
						SpawnSam();
					}
				}
				else
				{
					SpawnUggWrongway();
				}
			}
		}
		else
		{
			SpawnUggWrongway();
		}
	}
}

void EnemyHandeler::SetCanMove( bool move )
{
	for ( auto enemy : m_EnemiesGameObjects )
	{
		if( enemy == nullptr ) continue;

		if ( enemy->GetComponent<SlickSam>() ) {
			enemy->GetComponent<SlickSam>()->SetCanMove( move );
		}
		else if ( enemy->GetComponent<UggWrongWay>() ) {
			enemy->GetComponent<UggWrongWay>()->SetCanMove( move );
		}
	}

	m_pCoily->GetComponent<Coily>()->SetCanMove( move );
}

void EnemyHandeler::SetHasCoily( bool hasCoily )
{
	m_HasCoily = hasCoily;
	m_pCoily = nullptr;
}

void EnemyHandeler::Clear()
{
	m_HowManyEnemies = 0;
	m_HasCoily = false;
	m_pCoily = nullptr;
	m_EnemiesGameObjects.clear();
}
