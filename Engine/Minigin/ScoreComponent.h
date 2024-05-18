#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
namespace dae
{
	class BaseComponent;

	class ScoreComponent: public TextComponent
	{
		public:
		ScoreComponent( GameObject* parentGameObject, const std::string& text, std::shared_ptr<Font> font, int score = 0 );
		virtual ~ScoreComponent() = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void SetScore(int score);
		void ResetScore();
		int GetScore() const { return m_Score; }

		private:
			int m_Score;
	};
}

