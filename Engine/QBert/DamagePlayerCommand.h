#pragma once
#include "InputCommands.h"
#include "QBert.h"
#include "GameObject.h"

class DamagePlayerCommand : public dae::GameObjectCommand
{
public:
	DamagePlayerCommand( dae::GameObject* gameObject, QBert* player ) : GameObjectCommand( gameObject ){ m_pPlayer = player; }
	virtual ~DamagePlayerCommand() = default;

	virtual void Execute() override
	{
		if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
		{
			GetPlayer()->GetsHit();
		}
	}

protected:
	QBert* GetPlayer(){return m_pPlayer; }

private:
	dae::GameObject* m_pGameObject{};
	QBert* m_pPlayer;
};