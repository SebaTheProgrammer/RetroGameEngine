
#include "InputCommands.h"
#include "ButtonManagerComponent.h"
#include <iostream>

void dae::NextButtonCommand::Execute( )
{
	if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
	{
		auto buttonmanagers = GetGameObject()->GetComponents <ButtonManagerComponent>();

		for ( auto& buttonmanager : buttonmanagers )
		{
			buttonmanager->SelectNextButton( m_HowMany );
		}
	}
}

void dae::PreviousButtonCommand::Execute( )
{
	if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
	{
		auto buttonmanagers = GetGameObject()->GetComponents <ButtonManagerComponent>();

		for ( auto& buttonmanager : buttonmanagers )
		{
			buttonmanager->SelectPreviousButton( m_HowMany );
		}
	}
}

void dae::PressButtonCommand::Execute()
{
	if ( dae::SceneManager::GetInstance().GetCurrentSceneIndex() == GetGameObject()->GetSceneIndex() || dae::SceneManager::GetInstance().GetCurrentSceneIndex() == -1 )
	{
		auto buttonmanagers = GetGameObject()->GetComponents <ButtonManagerComponent>();

		for ( auto& buttonmanager : buttonmanagers )
		{
			buttonmanager->PressSelectedButton();
		}
	}
}
