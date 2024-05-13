#include "Level.h"
#include "GameObject.h"
#include "PyramidCubes.h"
#include "Qbert.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "AnimatedTextureComponent.h"
#include "PlayerCommands.h"
#include "LevelHandeler.h"
#include <iostream>
#include "HealthComponentQbert.h"
#include <GameTime.h>

Level::Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level, 
	std::shared_ptr<dae::Texture2D> idle, std::shared_ptr<dae::Texture2D> backface, int qbertlives )
	: dae::BaseComponent( parentGameObject )
{
	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;

	//bg
	std::string bgFilename = "bg" + std::to_string( level) + ".png";
	auto background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( background );

	//pyramid base
	m_PyramidGameObject = std::make_shared<dae::GameObject>( level);
	auto pyramid = std::make_shared<PyramidCubes>( m_PyramidGameObject.get(), howLongLevel, level - 1);
	m_PyramidGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x,parentGameObject->GetLocalTransform().GetPosition().y } );
	m_PyramidGameObject->AddComponent( pyramid );

	//begin
	m_BeginScreenObject = std::make_shared<dae::GameObject>( level);
	std::string beginFilename = "Level 0" + std::to_string( level) + " Title.png";
	auto begin = std::make_shared<dae::TextureComponent>( parentGameObject, beginFilename );
	begin->SetLocalPosition( -begin->GetWidth() / 2+30, parentGameObject->GetLocalTransform().GetPosition().y / 2 - begin->GetHeight() / 2 );
	m_BeginScreenObject->AddComponent( begin );

	//players
	multiplayer = multiplayer; //TODO: if multiplayer, add 2 players, but is for later
	m_QbertGameObject = std::make_shared<dae::GameObject>( level);
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40 } );
	auto qbert = std::shared_ptr<QBert>{};

	qbert = ( std::make_shared<QBert>( m_QbertGameObject.get(), idle, backface, true) );
	m_QbertGameObject->AddComponent( qbert );

	//Levelhandeler
	auto levelHandeler = std::make_shared<LevelHandeler>( m_PyramidGameObject.get(), qbertlives);
	m_PyramidGameObject->AddComponent( levelHandeler );

	pyramid->AddObserver( levelHandeler.get() );
	qbert->AddObserver( levelHandeler.get() );

	//Health display
	auto healthDisplay = std::make_shared<HealthComponentQbert>( m_PyramidGameObject.get(), levelHandeler->GetLives(), true);
	healthDisplay->SetLocalPosition( -250, -50 );
	m_PyramidGameObject->AddComponent( healthDisplay );
}

void Level::Update()
{
	if ( m_Begin )
	{
		m_BeginTimer += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_BeginTimer > m_BeginTime )
		{
			m_Begin = false;
		}
		m_BeginScreenObject->Update();
	}
	else 
	{
		m_PyramidGameObject->Update();
		m_QbertGameObject->Update();
	}
}

void Level::Render() const
{
	if ( m_Begin )
	{
		m_BeginScreenObject->Render();
	}
	else
	{
		m_PyramidGameObject->Render();
		m_QbertGameObject->Render();
	}
}
