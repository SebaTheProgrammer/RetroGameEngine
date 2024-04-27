#include "Level.h"
#include "GameObject.h"
#include "PyramidCubes.h"
#include "Qbert.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "AnimatedTextureComponent.h"
#include "DamagePlayerCommand.h"

Level::Level( dae::GameObject* parentGameObject, bool multiplayer, int howLongLevel, int level )
	: dae::BaseComponent( parentGameObject )
{
	if ( level > m_MAX_LEVEL ) level = m_MAX_LEVEL;

	//bg
	std::string bgFilename = "bg" + std::to_string( level + 1 ) + ".png";
	m_Background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	m_Background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( m_Background );

	//pyramid base
	m_pPyramid = std::make_shared<PyramidCubes>( parentGameObject, howLongLevel, level );
	parentGameObject->AddComponent( m_pPyramid );

	//players
	multiplayer = multiplayer;

	m_QbertGameObject = new dae::GameObject( level + 1 );
	m_QbertGameObject->SetLocalTransform( { parentGameObject->GetLocalTransform().GetPosition().x, parentGameObject->GetLocalTransform().GetPosition().y - 40 } );
	auto qbert = std::shared_ptr<QBert>{};

	qbert = ( std::make_shared<QBert>( m_QbertGameObject,
		dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
		dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
		dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
		dae::ResourceManager::GetInstance().LoadTexture( "qbertIdle.png" ),
		true ) );
	m_QbertGameObject->AddComponent( qbert );

	//Stats
	m_pStats = std::make_shared<PlayerStats>( m_QbertGameObject, 3 );
	m_QbertGameObject->AddComponent( m_pStats );
	qbert->AddObserver( m_pStats.get() );

	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 18 );
	m_pHealthDisplay = std::make_shared<dae::TextComponent>( m_QbertGameObject, "Health: " + std::to_string( m_pStats->GetLives() ), font );
	m_pHealthDisplay->SetLocalPosition( -250, -50 );
	m_QbertGameObject->AddComponent( m_pHealthDisplay );
	m_pHealthDisplay->SetText( "Health: " + std::to_string( m_pStats->GetLives()) );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_C, InputTypeKeyBoard::IsDownThisFrame, DamagePlayerCommand{ m_QbertGameObject, qbert.get()});
}

Level::~Level()
{
	delete m_QbertGameObject;
}

void Level::Update()
{
	m_Background->Update();

	m_pPyramid->Update();

	m_QbertGameObject->Update();
}

void Level::Render() const
{
	m_Background->Render();

	m_pPyramid->Render();

	m_QbertGameObject->Render();
}
