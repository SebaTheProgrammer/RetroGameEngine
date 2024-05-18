#include "ScoreComponent.h"


dae::ScoreComponent::ScoreComponent( GameObject* parentGameObject, std::shared_ptr<Font> font, int score ) :
	TextComponent( parentGameObject, "Score: " + std::to_string( score ), font ),
	m_Score( score )
{
}

void dae::ScoreComponent::AddScore( int score )
{
	m_Score += score;
	SetText( "Score: " + std::to_string( m_Score ) );
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
	SetText( "Score: " + std::to_string( m_Score ) );
}
