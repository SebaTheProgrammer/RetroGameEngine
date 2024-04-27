#include "PlayerStats.h"
#include <iostream>
#include "GameObject.h"
#include <TextComponent.h>
#include "QBert.h"

PlayerStats::PlayerStats( dae::GameObject* const parentGameObject, int lives ):
	BaseComponent( parentGameObject ),
	m_Lives( lives ), m_Score(0)
{
}

PlayerStats::~PlayerStats()
{
}

void PlayerStats::Update()
{
	if ( m_NeedsUpdate )
	{
		if ( dae::TextComponent * textComponent{ GetOwner()->GetComponent<dae::TextComponent>().get()} )
		{
			textComponent->SetText(
				"Health: " +
				std::to_string( m_Lives )
			);
		}
		m_NeedsUpdate = false;
	}
}

void PlayerStats::Notify( dae::EventType event, dae::GameObject* gameObj )
{
	if ( QBert * qbert{ gameObj->GetComponent<QBert>().get()} )
	{
		switch ( event )
		{
		case dae::EventType::PLAYER_DIED:
			std::cout << "PLAYER DIED" << std::endl;
			break;
		case dae::EventType::PLAYER_HIT:
			--m_Lives;
			break;
		case dae::EventType::KILL_ENEMY:
			m_Score += 100;
			break;
		}

		m_NeedsUpdate = true;
	}
}

void PlayerStats::SetLives( int lives )
{	
	m_NeedsUpdate = true;
	m_Lives = lives;
}

void PlayerStats::SetScore( int score )
{
	m_NeedsUpdate = true;
	m_Score = score;
}

int PlayerStats::GetLives() const
{	
	return m_Lives;
}

int PlayerStats::GetScore() const
{
	return m_Score;
}
