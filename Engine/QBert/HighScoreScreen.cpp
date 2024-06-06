#include "HighScoreScreen.h"
#include "ScoreFile.h"
#include <TextComponent.h>
#include <ResourceManager.h>
#include <TextureComponent.h>
#include "TextComponent.h"
#include <GameTime.h>
#include "Commands.h"
#include <ButtonManagerComponent.h>

HighScoreScreen::HighScoreScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font1, std::shared_ptr<dae::Font> font2 )
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
		m_TextComponents[ index ]->SetLocalPosition( ( 640 - m_TextComponents[ index ]->GetTexture()->GetWidth() ) / 2, 100.f+ index*30.f );
		parentGameObject->AddComponent( m_TextComponents[index]);
	}

	m_ButtonsHandeler = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
	std::shared_ptr<dae::Command> back = std::make_shared< OpenMainMenuCommand>( m_ButtonsHandeler.get() );
	auto buttonB = std::make_shared<dae::ButtonComponent>( m_ButtonsHandeler.get(), "Back", font1, back );
	m_ButtonsHandeler->SetLocalTransform( { 540, 425 } );
	m_ButtonsHandeler->AddComponent( buttonB );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_SPACE, InputTypeKeyBoard::IsDownThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
	std::vector<std::shared_ptr<dae::ButtonComponent>> allButtonsHighscore = { buttonB };
	auto buttonManagerHighscore = std::make_shared<dae::ButtonManagerComponent>( m_ButtonsHandeler.get(), arrow, allButtonsHighscore );
	m_ButtonsHandeler->AddComponent( buttonManagerHighscore );
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
	if ( m_NeedsUpdate )
	{
		m_NeedsUpdate = false;
		GetAllScores();
	}

	m_ButtonsHandeler->Update();
}

void HighScoreScreen::Render() const
{
	m_ButtonsHandeler->Render();
}
