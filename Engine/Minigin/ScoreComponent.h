#pragma once
#include "BaseComponent.h"

namespace dae
{
	class BaseComponent;

	class ScoreComponent: public BaseComponent
	{
		public:
		ScoreComponent(GameObject* const parentGameObject, int score);
		virtual ~ScoreComponent() = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void AddScore(int score);
		void ResetScore();
		int GetScore() const { return m_Score; }

		private:
			int m_Score;
	};
}

