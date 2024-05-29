#pragma once
#include "InputCommands.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level.h"
#include <iostream>

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