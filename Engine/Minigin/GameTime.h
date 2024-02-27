#pragma once
#include <memory>

namespace dae
{
	class GameTime final
	{
	public:
		static GameTime& GetInstance()
		{
			static GameTime instance{};
			return instance;
		}

		float GetDeltaTime() const { return m_DeltaTime; }
		void SetDeltaTime(float deltaTime) { m_DeltaTime = deltaTime; }

		GameTime(const GameTime& other) = delete;
		GameTime(GameTime&& other) = delete;
		GameTime& operator=(const GameTime& other) = delete;
		GameTime& operator=(GameTime&& other) = delete;

	private:
		GameTime() = default;
		float m_DeltaTime;
	};
}