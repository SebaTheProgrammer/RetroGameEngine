#pragma once
#include "BaseComponent.h"
#include <string>
#include <GameObject.h>
#include <Font.h>
#include <TextComponent.h>
class HighScoreScreen : public dae::BaseComponent
{
	public:
		HighScoreScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font1, std::shared_ptr<dae::Font> font2 );
		~HighScoreScreen() = default;

		HighScoreScreen(const HighScoreScreen& other) = delete;
		HighScoreScreen(HighScoreScreen&& other) = delete;
		HighScoreScreen& operator=(const HighScoreScreen& other) = delete;
		HighScoreScreen& operator=(HighScoreScreen&& other) = delete;

		void GetAllScores();

		void Update() override;

		void Render() const override;

		void AssignControllerInput();

private:

	std::vector < std::pair<std::string, int>> m_Scores;
	std::vector < std::shared_ptr<dae::TextComponent>> m_TextComponents;

	std::shared_ptr<dae::GameObject> m_ButtonsHandeler;

	bool m_NeedsUpdate = true;
};