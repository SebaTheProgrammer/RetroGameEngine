#pragma once
#include <string>
#include <memory>

namespace dae
{
	class Font;
	class Texture2D;
	class Component;
	class GameObject;
	class Transform;

	class TextComponent final: public Component
	{
	public:

		TextComponent(GameObject* gameObject);

		virtual ~TextComponent() = default;
		TextComponent( const TextComponent& other )=delete;
		TextComponent( TextComponent&& other ) = delete;
		TextComponent& operator=( const TextComponent& other ) = delete;
		TextComponent& operator=( TextComponent&& other ) = delete;

		void Update() override;
		void Render() const override;

		void SetText( const std::string& text );
		void SetPosition( float x, float y );

		void SetFont( std::shared_ptr<Font> font );

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

		GameObject* m_pGameObject = nullptr;
	};
}

