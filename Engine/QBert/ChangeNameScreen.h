#pragma once
#include "BaseComponent.h"
#include <TextComponent.h>
#include <TextureComponent.h>
#include "ScoreFile.h"

class ChangeNameScreen : public dae::BaseComponent
{
	public:
	ChangeNameScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font );
	virtual ~ChangeNameScreen() = default;

	void Update() override;
	void Render() const override;

	void SetName( std::string name );
	std::string GetName() const { return  ScoreFile::GetInstance().GetName(); };

	private:
		std::shared_ptr<dae::GameObject> m_ButtonsHandeler;
		std::vector< std::shared_ptr <dae::GameObject>> m_Buttons;

		std::string m_Name;
		std::shared_ptr<dae::TextComponent > m_NameText;
};

