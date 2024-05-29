#pragma once
#include "BaseComponent.h"
#include "AnimatedTextureComponent.h"
#include "Observer.h"
#include "GameObject.h"
#include "GameActor.h"

class Cube : public dae::BaseComponent, public dae::GameActor
{
	public:

	Cube( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int level, int howManuJumpsNeeded );
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
	void ReverseOne();
	void Reset();

	bool IsCompleted() const { return m_Completed; }
	void CompletedCube();

	private:
		int m_HowManyJumpsNeeded;

		std::shared_ptr<dae::AnimatedTextureComponent> m_pTexture;

		float m_X;
		float m_Y;

		float m_WinFrameTime = 0.7f;

		int m_CurrentFrame = 0;
		int m_Level;

		bool m_Completed = false;
};

