#pragma once
#include "BaseComponent.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"

namespace dae
{
	class ButtonComponent;

	class ButtonManagerComponent : public BaseComponent
	{
		public:
		ButtonManagerComponent( GameObject* const parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::vector<std::shared_ptr<ButtonComponent>> buttons );
		virtual ~ButtonManagerComponent() = default;

		ButtonManagerComponent( const ButtonManagerComponent& other ) = delete;
		ButtonManagerComponent( ButtonManagerComponent&& other ) = delete;
		ButtonManagerComponent& operator=( const ButtonManagerComponent& other ) = delete;
		ButtonManagerComponent& operator=( ButtonManagerComponent&& other ) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void AddButton( std::shared_ptr<ButtonComponent> button );
		void RemoveButton( std::shared_ptr<ButtonComponent> button );

		void SetSelectedButton( std::shared_ptr<ButtonComponent> button );
		std::shared_ptr<ButtonComponent> GetSelectedButton() const { return m_SelectedButton; }

		void SelectNextButton(int howMany);
		void SelectPreviousButton( int howMany );

		void PressSelectedButton();

		private:

			std::vector<std::shared_ptr<ButtonComponent>> m_Buttons;
			std::shared_ptr<ButtonComponent> m_SelectedButton;

			std::shared_ptr<dae::TextureComponent> m_Arrow;

			float m_TimeSinceLastButtonPress{ 0.f };
			float m_ButtonPressDelay{ 0.2f };
			bool m_CanPressButton{ true };

			glm::vec2 m_ArrowOffset{ -17.f, 3.f };
	};
}

