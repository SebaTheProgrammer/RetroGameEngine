#pragma once
#include <string>
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public TextComponent
	{

	public:
		FPSComponent() = default;
		virtual ~FPSComponent() = default;

		FPSComponent( const FPSComponent& other ) = delete;
		FPSComponent( FPSComponent&& other ) = delete;
		FPSComponent& operator=( const FPSComponent& other ) = delete;
		FPSComponent& operator=( FPSComponent&& other ) = delete;

		void Update() override;

		private:
			bool m_NeedsUpdate;
			std::string m_Text;
			Transform m_Transform{};
			std::shared_ptr<Font> m_Font;
			std::shared_ptr<Texture2D> m_TextTexture;
			int m_Size;
	};
}
