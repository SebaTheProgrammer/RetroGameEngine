#include "ScoreComponent.h"


dae::ScoreComponent::ScoreComponent( GameObject* parentGameObject, const std::string& text, std::shared_ptr<Font> font, int score ) :
	TextComponent( parentGameObject, text + std::to_string( score ), font ),
	m_Score( score )
{
}

void dae::ScoreComponent::SetScore( int score )
{
	m_Score = score;
	SetText( "Score: " + std::to_string( m_Score ) );
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	SetText( "Score: " + std::to_string( m_Score ) );
}
