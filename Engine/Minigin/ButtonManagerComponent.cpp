#include "ButtonManagerComponent.h"
#include <iostream>
#include "TextureComponent.h"

dae::ButtonManagerComponent::ButtonManagerComponent( GameObject* const parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::vector<std::shared_ptr<ButtonComponent>> buttons )
	: BaseComponent( parentGameObject ),
	m_Buttons{ buttons }
{
	if ( !m_Buttons.empty() )
	{
		m_SelectedButton = m_Buttons[0];
	}

	m_Arrow = std::make_shared<dae::TextureComponent>( parentGameObject, arrow );
}

void dae::ButtonManagerComponent::Update()
{
	m_Arrow->Update();
}

void dae::ButtonManagerComponent::Render() const
{
	m_Arrow->Render();
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

			m_Arrow->SetLocalPosition( m_SelectedButton->GetLocalPosition().x - GetOwner()->GetLocalTransform().GetPosition().x, 
				m_SelectedButton->GetLocalPosition().y - GetOwner()->GetLocalTransform().GetPosition().y );
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

			m_Arrow->SetLocalPosition( m_SelectedButton->GetLocalPosition().x - GetOwner()->GetLocalTransform().GetPosition().x,
				m_SelectedButton->GetLocalPosition().y - GetOwner()->GetLocalTransform().GetPosition().y );
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
