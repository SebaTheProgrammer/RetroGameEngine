#pragma once
#include <string>
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>
#include "GameEvents.h"

namespace dae
{
	class BaseComponent;
	class OnTextChangedEvent;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent( GameObject* parentGameObject, const std::string& text, std::shared_ptr<Font> font, bool standStill = false );
		virtual ~TextComponent() = default;

		TextComponent( const TextComponent& other ) = delete;
		TextComponent( TextComponent&& other ) = delete;
		TextComponent& operator=( const TextComponent& other ) = delete;
		TextComponent& operator=( TextComponent&& other ) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void SetText( const std::string& text );
		virtual void GetText() { m_Text; }
		virtual void SetPosition( float x, float y );

	private:
		bool m_NeedsUpdate;
		bool m_StandStill;
		std::string m_Text;
		Transform m_Transform{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}

