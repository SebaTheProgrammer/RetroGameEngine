#include "ButtonManagerComponent.h"
#include <iostream>

dae::ButtonManagerComponent::ButtonManagerComponent( GameObject* const parentGameObject, std::vector<std::shared_ptr<ButtonComponent>> buttons )
	: BaseComponent( parentGameObject ),
	m_Buttons{ buttons }
{
	if ( !m_Buttons.empty() )
	{
		m_SelectedButton = m_Buttons[0];
	}
}

void dae::ButtonManagerComponent::AddButton( std::shared_ptr<ButtonComponent> button )
{
	m_Buttons.push_back( button );
}

void dae::ButtonManagerComponent::RemoveButton( std::shared_ptr<ButtonComponent> button )
{
	m_Buttons.erase( std::remove( m_Buttons.begin(), m_Buttons.end(), button ), m_Buttons.end() );
}

void dae::ButtonManagerComponent::SetSelectedButton( std::shared_ptr<ButtonComponent> button )
{
	m_SelectedButton = button;
}

void dae::ButtonManagerComponent::SelectNextButton()
{
	if ( m_SelectedButton )
	{
		auto it = std::find( m_Buttons.begin(), m_Buttons.end(), m_SelectedButton );
		if ( it != m_Buttons.end() )
		{
			++it;
			if ( it == m_Buttons.end() )
			{
				it = m_Buttons.begin();
			}
			m_SelectedButton = *it;
		}
	}
}

void dae::ButtonManagerComponent::SelectPreviousButton()
{
	if ( m_SelectedButton )
	{
		auto it = std::find( m_Buttons.begin(), m_Buttons.end(), m_SelectedButton );
		if ( it != m_Buttons.end() )
		{
			if ( it == m_Buttons.begin() )
			{
				it = m_Buttons.end();
			}
			--it;
			m_SelectedButton = *it;
		}
	}
}

void dae::ButtonManagerComponent::PressSelectedButton()
{
	if ( m_SelectedButton )
	{
		m_SelectedButton->Clicked();
	}
}
