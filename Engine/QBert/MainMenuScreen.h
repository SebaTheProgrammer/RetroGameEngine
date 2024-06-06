#pragma once
#include "BaseComponent.h"
#include <TextComponent.h>
#include <TextureComponent.h>
#include "HighScoreScreen.h"

class MainMenuScreen : public dae::BaseComponent
{
public:
	MainMenuScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font, HighScoreScreen* score, int max );
	virtual ~MainMenuScreen() = default;

	void Update() override;
	void Render() const override;

private:
	std::vector< std::shared_ptr <dae::GameObject>> m_Buttons;
	std::shared_ptr<dae::GameObject> m_ButtonsHandeler;
};

