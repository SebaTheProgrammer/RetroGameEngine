#include "ButtonManagerComponent.h"
#include <iostream>
#include "TextureComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"

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

	if ( m_SelectedButton ) 
	{
		m_Arrow->SetLocalPosition( m_SelectedButton->GetLocalPosition().x - GetOwner()->GetLocalTransform().GetPosition().x + m_ArrowOffset.x,
			m_SelectedButton->GetLocalPosition().y - GetOwner()->GetLocalTransform().GetPosition().y + m_ArrowOffset.y );
	}

	if ( !m_CanPressButton )
	{
		m_TimeSinceLastButtonPress += dae::GameTime::GetInstance().GetDeltaTime();
		if ( m_TimeSinceLastButtonPress >= m_ButtonPressDelay )
		{
			m_CanPressButton = true;
			m_TimeSinceLastButtonPress = 0.f;
		}
	}
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

void dae::ButtonManagerComponent::SelectNextButton( int howMany )
{
	if ( m_SelectedButton )
	{
		for ( int i{}; i < howMany; ++i ) {
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
		auto& ss = dae::ServiceLocator::GetSoundSystem();
		ss.AddSound( "Change", "Sounds/Change Selection.wav" );
		ss.Play( ss.GetSoundId( "Change" ), 50 );
	}
}

void dae::ButtonManagerComponent::SelectPreviousButton( int howMany )
{
	if ( m_SelectedButton )
	{
		for ( int i{}; i < howMany; ++i ) {
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
		auto& ss = dae::ServiceLocator::GetSoundSystem();
		ss.AddSound( "Change", "Sounds/Change Selection.wav" );
		ss.Play( ss.GetSoundId( "Change" ), 50 );
	}
}

void dae::ButtonManagerComponent::PressSelectedButton()
{
	if ( m_SelectedButton && m_CanPressButton )
	{
		m_SelectedButton->Clicked();
		m_CanPressButton = false;

		auto& ss = dae::ServiceLocator::GetSoundSystem();
		ss.AddSound( "Change", "Sounds/Change Selection.wav" );
		ss.Play( ss.GetSoundId( "Change" ), 50 );
	}
}
