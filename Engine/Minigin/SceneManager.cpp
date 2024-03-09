#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_Scenes[ m_CurrentSceneIndex ]->Update();
}

void dae::SceneManager::FixedUpdate()
{
	m_Scenes[ m_CurrentSceneIndex ]->FixedUpdate();;
}

void dae::SceneManager::LateUpdate()
{
	m_Scenes[ m_CurrentSceneIndex ]->LateUpdate();
}

void dae::SceneManager::Render()
{
	m_Scenes[ m_CurrentSceneIndex ]->Render();
}

dae::Scene& dae::SceneManager::CreateScene( const std::string& name )
{
	const auto& scene = std::shared_ptr<Scene>( new Scene( name ) );
	m_Scenes.push_back( scene );
	++m_CurrentSceneIndex;

	return *scene;
}
