#include "HighScoreScreen.h"
#include "ScoreFile.h"
#include <TextComponent.h>
#include <ResourceManager.h>
#include <TextureComponent.h>
#include "TextComponent.h"
#include <GameTime.h>

HighScoreScreen::HighScoreScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Font> font1, std::shared_ptr<dae::Font> font2 )
	: BaseComponent( parentGameObject )
{
	std::string bgFilename = "bg2.png";
	auto background = std::make_shared<dae::TextureComponent>( parentGameObject, bgFilename );
	background->SetLocalPosition( -parentGameObject->GetLocalTransform().GetPosition().x, -parentGameObject->GetLocalTransform().GetPosition().y );
	parentGameObject->AddComponent( background );

	m_Scores = ScoreFile::GetInstance().ReadHighScores();
	auto textScore = std::make_shared<dae::TextComponent>( parentGameObject, "HIGH SCORES: ", font1, true);
	textScore->SetLocalPosition( 200, 50.f);
	parentGameObject->AddComponent( textScore );

	m_TextComponents.resize( 10 );

	for ( unsigned index{};index < m_TextComponents.size(); ++index )
	{
		std::string text = m_Scores[index].first + " " + std::to_string( m_Scores[index].second );
		m_TextComponents[index] = std::make_shared<dae::TextComponent>(parentGameObject, text, font2, true);
		m_TextComponents[ index ]->SetLocalPosition( 225, 100.f+ index*30.f );
		parentGameObject->AddComponent( m_TextComponents[index]);
	}
}

void HighScoreScreen::GetAllScores()
{
	m_Scores = ScoreFile::GetInstance().ReadHighScores();

	for ( unsigned index{}; index < m_TextComponents.size(); ++index )
	{
		std::string text = m_Scores[index].first + " " + std::to_string( m_Scores[index].second );
		m_TextComponents[index]->SetText( text );
	}
}

void HighScoreScreen::Update()
{
	//normally load only when just opened, but therefor i need a button class
	if ( m_NeedsUpdate )
	{
		m_NeedsUpdate = false;
		GetAllScores();
	}

	m_UpdateTime+= dae::GameTime::GetInstance().GetDeltaTime();

	if ( m_UpdateTime > 1.f )
	{
		m_UpdateTime = 0.f;
		m_NeedsUpdate = true;
	}
}
