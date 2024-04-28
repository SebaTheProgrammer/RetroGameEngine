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

Level::Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level )
	: dae::BaseComponent( parentGameObject )
{
	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;

	//bg
	std::string bgFilename = "bg" + std::to_string( level + 1 ) + ".png";
	auto background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( background );

	//pyramid base
	auto pyramid = std::make_shared<PyramidCubes>( parentGameObject, howLongLevel, level);
	parentGameObject->AddComponent( pyramid );

	//players
	multiplayer = multiplayer;
	m_QbertGameObject = new dae::GameObject(level + 1);
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40 } );
	auto qbert = std::shared_ptr<QBert>{};

	qbert = ( std::make_shared<QBert>( m_QbertGameObject,
		dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
		dae::ResourceManager::GetInstance().LoadTexture( "qbertBackFaceIdle.png" ),
		true ) );
	m_QbertGameObject->AddComponent( qbert );

	//Levelhandeler
	auto stats = std::make_shared<LevelHandeler>( parentGameObject, 3);
	parentGameObject->AddComponent( stats );

	pyramid->AddObserver( stats.get() );
	qbert->AddObserver( stats.get() );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );
	auto healthDisplay = std::make_shared<dae::TextComponent>( parentGameObject, "Health: " + std::to_string(stats->GetLives()), font, true);
	healthDisplay->SetLocalPosition( 50, 50 );
	parentGameObject->AddComponent( healthDisplay );
	healthDisplay->SetText( "Health: " + std::to_string( stats->GetLives()) );

	//Debug damage
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_C, InputTypeKeyBoard::IsDownThisFrame, DamagePlayerCommand{ m_QbertGameObject, qbert.get()});
}

Level::~Level()
{
	delete m_QbertGameObject;
}

void Level::Update()
{
	m_QbertGameObject->Update();
}

void Level::Render() const
{
	m_QbertGameObject->Render();
}
