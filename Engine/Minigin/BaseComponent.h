#pragma once

namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent( const BaseComponent& other ) = delete;
		BaseComponent( BaseComponent&& other ) = delete;
		BaseComponent& operator=( const BaseComponent& other ) = delete;
		BaseComponent& operator=( BaseComponent&& other ) = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;

	protected:
		//virtual void Initialize() = 0;
		//virtual void LateInitialize() = 0;
		//virtual void Start() = 0;
		//virtual void FixedUpdate() = 0;
		//virtual void PreRender() = 0;
		//virtual void PostRender() = 0;
		//virtual void Destroy() = 0;
		//virtual void OnCollision() = 0;
		//virtual void OnEnable() = 0;
		//virtual void OnDisable() = 0;


	private:
		//GameObject* m_pGameObject;
	};
}

