#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::FixedUpdate( float fixedTime )
{
	//Physics and networking
	fixedTime += fixedTime;
}

void dae::SceneManager::Update()
{
	//update
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::LateUpdate()
{
	//extra update for example the camera

}


void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
