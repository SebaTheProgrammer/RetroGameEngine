#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>
#include <memory>
#include "GameObject.h"

namespace dae
{
	class BaseComponent;
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
		public:
		TextureComponent( GameObject* parentGameObject, const std::string& fileName );
		TextureComponent( GameObject* parentGameObject, const std::shared_ptr<Texture2D> texture );
		virtual ~TextureComponent() = default;

		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);

		float GetWidth() const { return m_pTexture->GetWidth(); }
		float GetHeight() const { return m_pTexture->GetHeight(); }

		private:
			std::shared_ptr<Texture2D> m_pTexture;
			float m_X;
			float m_Y;
	};
}

