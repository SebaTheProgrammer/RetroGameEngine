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

	protected:
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

	class SingleMoveCommand : public GameObjectCommand
	{
	public:

		SingleMoveCommand( GameObject* gameObject, glm::vec2 direction ) : GameObjectCommand( gameObject )
		{
			m_Direction = direction;
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
			{
				if ( auto movementComp{ GetGameObject()->GetComponent<dae::SingleMovementComponent>() } )
				{
					movementComp->SingleMove( m_Direction );
				}
			}
		}

	private:

		glm::vec2 m_Direction;
	};

	class AnimationCommand : public GameObjectCommand
	{
	public:
		AnimationCommand( GameObject* gameObject, int animation ) : GameObjectCommand( gameObject )
		{
			m_Animation = animation;
		}

		virtual void Execute() override
		{
			if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
			{
				//if ( auto animationComp{ GetGameObject()->GetComponent<dae::AnimatedTextureComponent>() } )
				{
					//animationComp->SetAnimation( m_Animation );
				}
			}
		}

		private:
			int m_Animation{};
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
					scoreComp->AddScore( m_Score );
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
}
