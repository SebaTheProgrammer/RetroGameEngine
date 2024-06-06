#pragma once
#include "InputCommands.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level.h"
#include <iostream>
#include "HighScoreScreen.h"
#include <ServiceLocator.h>
#include "ChangeNameScreen.h"

class OpenMainMenuCommand : public dae::GameObjectCommand
{
public:
	OpenMainMenuCommand( dae::GameObject* gameObject ) : dae::GameObjectCommand( gameObject ) {}

	virtual void Execute() override
	{
		if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
		{
			dae::SceneManager::GetInstance().SetCurrentScene( 0 );
		}
	}
};

class MultiplayerCommand : public dae::GameObjectCommand
{
public:
	MultiplayerCommand( dae::GameObject* gameObject ) : dae::GameObjectCommand( gameObject ) {}

	virtual void Execute() override
	{
		if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
		{
			auto scenes = dae::SceneManager::GetInstance().GetScenes();
			for ( auto& scene : scenes )
			{
				auto objects = scene->GetObjects();
				for ( auto& object : objects )
				{
					auto level = object->GetComponent<Level>();
					if ( level )
					{
						level->SetMultiplayer( true );
					}
				}
			}

			dae::SceneManager::GetInstance().SetCurrentScene( 1 );
		}
	}
};

class VersusCommand : public dae::GameObjectCommand
{
public:
	VersusCommand( dae::GameObject* gameObject ) : dae::GameObjectCommand( gameObject ) {}

	virtual void Execute() override
	{
		if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
		{
			auto scenes = dae::SceneManager::GetInstance().GetScenes();
			for ( auto& scene : scenes )
			{
				auto objects = scene->GetObjects();
				for ( auto& object : objects )
				{
					auto level = object->GetComponent<Level>();
					if ( level )
					{
						level->SetVersus( true );
					}
				}
			}

			dae::SceneManager::GetInstance().SetCurrentScene( 1 );
		}
	}
};

class SinglePlayer : public dae::GameObjectCommand
{
public:
	SinglePlayer( dae::GameObject* gameObject ) : dae::GameObjectCommand( gameObject ) {}

	virtual void Execute() override
	{
		if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
		{
			auto scenes = dae::SceneManager::GetInstance().GetScenes();
			for ( auto& scene : scenes )
			{
				auto objects = scene->GetObjects();
				for ( auto& object : objects )
				{
					auto level = object->GetComponent<Level>();
					if ( level )
					{
						level->SinglePlayer();
					}
				}
			}

			dae::SceneManager::GetInstance().SetCurrentScene( 1 );
		}
	}
};

class SoundCommand : public dae::Command
{
public:
	SoundCommand() {};

	virtual void Execute() override
	{
		auto& ss = dae::ServiceLocator::GetSoundSystem();
		if ( m_IsMuted )
		{
			m_IsMuted = false;
			ss.SetVolume( 100 );
		}
		else 
		{
			m_IsMuted = true;
			ss.SetVolume( 0 );
		}
	}

private:
		bool m_IsMuted{ false };
};


class OpenHighScoreCommand : public dae::GameObjectCommand
{
public:
	OpenHighScoreCommand( dae::GameObject* gameObject, int level, HighScoreScreen* highscore ) : GameObjectCommand( gameObject )
	{
		m_Level = level;
		m_pHighScore = highscore;
	}

	virtual void Execute() override
	{
		dae::SceneManager::GetInstance().SetCurrentScene( m_Level );
		m_pHighScore->GetAllScores();
	}

private:
	int m_Level{};
	HighScoreScreen* m_pHighScore{};
};

class OpenSceneWithIndex : public dae::GameObjectCommand
{
	public:
	OpenSceneWithIndex( dae::GameObject* gameObject, int level) : GameObjectCommand( gameObject )
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

class AddLetterCommand : public dae::GameObjectCommand
{
public:
	AddLetterCommand( dae::GameObject* gameObject, char letter ) : GameObjectCommand( gameObject )
	{
		m_Letter = letter;
	}

	virtual void Execute() override
	{
		auto changeNameScreen = GetGameObject()->GetComponent<ChangeNameScreen>();
		if ( changeNameScreen )
		{
			changeNameScreen->SetName( changeNameScreen->GetName() + m_Letter );
		}
	}

private:
	char m_Letter{};
};

class ClearLettersCommand : public dae::GameObjectCommand
{
public:
	ClearLettersCommand( dae::GameObject* gameObject ) : GameObjectCommand( gameObject ) {}

	virtual void Execute() override
	{
		auto changeNameScreen = GetGameObject()->GetComponent<ChangeNameScreen>();
		if ( changeNameScreen )
		{
			changeNameScreen->SetName( " " );
		}
	}

};