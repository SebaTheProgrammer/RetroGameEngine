#pragma once
#include "BaseComponent.h"
#include <string>
#include <GameObject.h>
#include <Font.h>
#include <TextComponent.h>
class HighScoreScreen : public dae::BaseComponent
{
	public:
		HighScoreScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Font> font1, std::shared_ptr<dae::Font> font2 );
		~HighScoreScreen() = default;

		HighScoreScreen(const HighScoreScreen& other) = delete;
		HighScoreScreen(HighScoreScreen&& other) = delete;
		HighScoreScreen& operator=(const HighScoreScreen& other) = delete;
		HighScoreScreen& operator=(HighScoreScreen&& other) = delete;

		void GetAllScores();

		void Update() override;

private:

	std::vector < std::pair<std::string, int>> m_Scores;
	std::vector < std::shared_ptr<dae::TextComponent>> m_TextComponents;

	bool m_NeedsUpdate = true;
	float m_UpdateTime = 0.f;
};