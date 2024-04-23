#include "Level.h"
#include "GameObject.h"
#include "PyramidCubes.h"
#include "Qbert.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "AnimatedTextureComponent.h"

Level::Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level )
	: dae::BaseComponent( parentGameObject )
{
	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;

	std::string bgFilename = "bg" + std::to_string( level+1 ) + ".png";
	m_Background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	m_Background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x,-parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( m_Background );

	//pyramid base
	m_pPyramid = std::make_shared<PyramidCubes>( parentGameObject, howLongLevel, level ); 
	parentGameObject->AddComponent( m_pPyramid );

	//players
	m_QbertGameObject = new dae::GameObject( level + 1);
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40} );

	if( multiplayer )
	{
		m_pQberts.push_back( std::make_shared<QBert>( m_QbertGameObject, 
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ), 
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ), 
			true ) );
		m_pQberts.push_back( std::make_shared<QBert>( m_QbertGameObject,
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			false ) );
	}
	else 
	{
		m_pQberts.push_back( std::make_shared<QBert>( m_QbertGameObject,
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
			true ) );
	}

	m_QbertGameObject->AddComponent( m_pQberts[ 0 ] );
	if( multiplayer )
	{
		m_QbertGameObject->AddComponent( m_pQberts[ 1 ] );
	}
}

Level::~Level()
{
	delete m_QbertGameObject;
}

void Level::Update()
{
	m_Background->Update();

	m_pPyramid->Update();

	for( auto& qbert : m_pQberts )
	{
		qbert->Update();
	}
}

void Level::Render() const
{
	m_Background->Render();

	m_pPyramid->Render();

	for( auto& qbert : m_pQberts )
	{
		qbert->Render();
	}
}
