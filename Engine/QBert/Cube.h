#pragma once
#include "BaseComponent.h"
#include "AnimatedTextureComponent.h"

class Cube : public dae::BaseComponent
{
	public:

	Cube( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int level );
	virtual ~Cube()= default;

	Cube( const Cube& other ) = delete;
	Cube( Cube&& other ) = delete;
	Cube& operator=( const Cube& other ) = delete;
	Cube& operator=( Cube&& other ) = delete;

	void Update() override;
	void Render() const override;

	void SetLocalPosition( float x, float y);

	void Won();

	void LandedOnThisCube();

	bool IsCompleted() const { return m_Completed; }

	private:
		std::shared_ptr<dae::AnimatedTextureComponent> m_pTexture;

		float m_X;
		float m_Y;

		float m_WinFrameTime = 0.5f;

		int m_CurrentFrame = 0;
		int m_Level;

		bool m_Completed = false;
};
