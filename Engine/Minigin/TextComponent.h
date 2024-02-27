#pragma once
#include <string>
#include "BaseComponent.h"
#include "Transform.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class BaseComponent;

	class TextComponent: public BaseComponent
	{
		public:
		TextComponent() = default;
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void SetText(const std::string& text);
		virtual void SetPosition(float x, float y);
		virtual void SetFont( const std::string& text);
		virtual void SetSize(int size);

		private:
			bool m_NeedsUpdate;
			std::string m_Text;
			Transform m_Transform{};
			std::shared_ptr<Font> m_Font;
			std::shared_ptr<Texture2D> m_TextTexture;
			int m_Size;
	};
}

