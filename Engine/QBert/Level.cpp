#include "Level.h"
#include "GameObject.h"
#include "PyramidCubes.h"
#include "Qbert.h"
#include "ResourceManager.h"

Level::Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level )
	: dae::BaseComponent( parentGameObject )
{
	//bg
	m_Background = std::make_shared <dae::TextureComponent>( parentGameObject, "bg1.png" );
	m_Background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( m_Background );

	//pyramid base
	m_pPyramid = std::make_shared<PyramidCubes>( parentGameObject, howLongLevel, level ); 
	parentGameObject->AddComponent( m_pPyramid );

	//players
	if( multiplayer )
	{
		m_pQberts.push_back( std::make_shared<QBert>( parentGameObject, true ) );
		m_pQberts.push_back( std::make_shared<QBert>( parentGameObject, false ) );
	}
	else 
	{
		m_pQberts.push_back( std::make_shared<QBert>( parentGameObject, true ) );
	}
	for ( auto& qbert : m_pQberts )
	{
		qbert->SetLocalPosition( 200, 200 );
	}
	parentGameObject->AddComponent( m_pQberts[0] );
	if( multiplayer )
	{
		parentGameObject->AddComponent( m_pQberts[1] );
	}
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
