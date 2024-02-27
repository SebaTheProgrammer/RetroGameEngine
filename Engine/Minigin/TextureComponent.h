#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <string>
#include <memory>

namespace dae
{
	class BaseComponent;
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
		public:
		TextureComponent(const std::string& filename);
		virtual ~TextureComponent() = default;

		void Update() override;
		void Render() const override;

		private:
				std::shared_ptr<Texture2D> m_pTexture;
				//GameObject* m_pGameObject;
	};
}

