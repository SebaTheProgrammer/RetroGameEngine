#pragma once
#include "BaseComponent.h"
#include <functional>
#include <string>
#include "InputManager.h"
#include "TextComponent.h"
#include "InputCommands.h"

namespace dae
{
	class Command;

	class ButtonComponent : public BaseComponent
	{
	public:
		ButtonComponent( GameObject* const parentGameObject, const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<dae::Command> command );
		virtual ~ButtonComponent() = default;

		ButtonComponent( const ButtonComponent& other ) = delete;
		ButtonComponent( ButtonComponent&& other ) = delete;
		ButtonComponent& operator=( const ButtonComponent& other ) = delete;
		ButtonComponent& operator=( ButtonComponent&& other ) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void Clicked();

		void SetText( const std::string& text );

		template<typename CommandType>
		void BindAction( std::shared_ptr<CommandType> command )
		{
			m_Command = command;
		}

		void SetLocalPosition( float x, float y );

	private:
		std::shared_ptr<dae::Command> m_Command;
		std::shared_ptr<TextComponent> m_TextComponent;

		float m_Width;
		float m_Height;
		float m_X;
		float m_Y;
	};
}

