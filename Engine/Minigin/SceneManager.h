#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene* GetCurrentScene() { return m_Scenes[ m_CurrentSceneIndex ].get(); }
		std::vector<std::shared_ptr<Scene>> GetScenes() { return m_Scenes; }
		void SetCurrentScene(int index) { m_CurrentSceneIndex = index; }
		int GetCurrentSceneIndex() { return m_CurrentSceneIndex; }
		size_t GetMaxScenes() { return m_Scenes.size(); }
		std::shared_ptr<Scene> GetScene(int index) { return m_Scenes[ index ]; }

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_CurrentSceneIndex{ -1 };
	};
}
