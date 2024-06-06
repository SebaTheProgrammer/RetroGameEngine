#pragma once
#include <memory>

#include "GameObject.h"
#include "MovenmentComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "SceneManager.h"
#include "SingleMovementComponent.h"

namespace dae
{
	class ButtonManagerComponent;

	class Command
	{
	public:

		virtual ~Command() {}
		virtual void Execute() = 0;

	};

	class GameObjectCommand : public Command
	{
	public:

		GameObjectCommand( GameObject* gameObject ) : m_pGameObject{ gameObject } {}
		virtual ~GameObjectCommand() {}

		GameObject* GetGameObject() const { return m_pGameObject; }

	private:
		GameObject* m_pGameObject{};
	};

	class MoveCommand : public GameObjectCommand
	{
	public:

		MoveCommand( GameObject* gameObject, glm::vec2 direction ) : GameObjectCommand( gameObject )
		{
			m_Direction = glm::normalize( glm::vec2{ direction.x, direction.y } );
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1)
			{
				if ( auto movementComp{ GetGameObject()->GetComponent<dae::MovenmentComponent>() } )
				{
					movementComp->Move( m_Direction );
				}
			}
		}

	private:

		glm::vec2 m_Direction;
	};

	class DealDamageCommand : public GameObjectCommand
	{
	public:
		DealDamageCommand( GameObject* gameObject, int damage ) : GameObjectCommand( gameObject ) 
		{
			m_Damage = damage;
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
			{
				if ( auto healthComp{ GetGameObject()->GetComponent<dae::HealthComponent>() } )
				{
					healthComp->TakeDamage( m_Damage );
				}
			}
		}

	private:
		
		int m_Damage{};
	};

	class HealCommand : public GameObjectCommand
	{
	public:
		HealCommand( GameObject* gameObject, int heal ) : GameObjectCommand( gameObject )
		{
			m_Heal = heal;
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
			{
				if ( auto healthComp{ GetGameObject()->GetComponent<dae::HealthComponent>() } )
				{
					healthComp->Heal( m_Heal );
				}
			}
		}
	private:
		int m_Heal{};
	};

	class AddScoreCommand : public GameObjectCommand
	{
	public:
		AddScoreCommand( GameObject* gameObject, int score ) : GameObjectCommand( gameObject )
		{
			m_Score = score;
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
			{
				if ( auto scoreComp{ GetGameObject()->GetComponent<dae::ScoreComponent>() } )
				{
					scoreComp->SetScore( m_Score );
				}
			}
		}
		private:
		int m_Score{};
	};

	class OpenLevelCommand : public GameObjectCommand
	{
	public:
		OpenLevelCommand( GameObject* gameObject, int level) : GameObjectCommand( gameObject )
		{
			m_Level = level;
		}

		virtual void Execute() override
		{
			dae::SceneManager::GetInstance().SetCurrentScene( m_Level );
		}

		private:
			int m_Level{};
	};

	class OpenNextLevelCommand : public GameObjectCommand
	{
	public:
		OpenNextLevelCommand( GameObject* gameObject ) : GameObjectCommand( gameObject ){}

		virtual void Execute() override
		{
			unsigned nextscene = dae::SceneManager::GetInstance().GetCurrentSceneIndex() + 1;

			if ( nextscene < dae::SceneManager::GetInstance().GetMaxScenes() )
			{
				dae::SceneManager::GetInstance().SetCurrentScene( nextscene );
			}
			else 
			{
				dae::SceneManager::GetInstance().SetCurrentScene( 0 );
			}
		}
	};

	class NextButtonCommand : public GameObjectCommand
	{
	public:

		NextButtonCommand( GameObject* gameObject, int howMany ) : GameObjectCommand( gameObject ) { m_HowMany = howMany; }

		virtual void Execute() override;

	private:
		int m_HowMany{};
	};

	class PreviousButtonCommand : public GameObjectCommand
	{
	public:

		PreviousButtonCommand( GameObject* gameObject, int howMany ) : GameObjectCommand( gameObject ) { m_HowMany = howMany; }

		virtual void Execute() override;

		private:
			int m_HowMany{};
	};

	class PressButtonCommand : public GameObjectCommand
	{
	public:

		PressButtonCommand( GameObject* gameObject ) : GameObjectCommand( gameObject ) {}

		virtual void Execute() override;
	};
}
