#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent( GameObject* const parentGameObject, int score ) :
	BaseComponent( parentGameObject ),
	m_Score( score )
{
}

void dae::ScoreComponent::AddScore( int score )
{
	m_Score += score;
}

void dae::ScoreComponent::ResetScore()
{
	m_Score = 0;
}
