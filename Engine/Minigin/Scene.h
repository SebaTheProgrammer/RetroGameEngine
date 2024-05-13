#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Initialize();

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void AttachToRoot( std::shared_ptr<GameObject> gameObject );
		void DettachFromRoot( GameObject* gameObject );
		std::shared_ptr<GameObject> GetChildSharedPtr( GameObject* child );
		std::vector < std::shared_ptr<GameObject>> GetObjects() const { return m_Objects; }
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects;

		static unsigned int m_idCounter; 
	};

}
