#pragma once
#include "BaseComponent.h"
#include "GameActor.h"
#include "PyramidCubes.h"

class SlickSam : public dae::BaseComponent, public dae::GameActor
{
public:
	SlickSam( dae::GameObject* parentGameObject,
		std::shared_ptr<dae::Texture2D> textureSlickSam, int levelSize, PyramidCubes* pyramid );
	~SlickSam() = default;
	SlickSam( const SlickSam& other ) = delete;
	SlickSam( SlickSam&& other ) = delete;
	SlickSam& operator=( const SlickSam& other ) = delete;
	SlickSam& operator=( SlickSam&& other ) = delete;

	enum class AnimationState
	{
		front,
		back//?
	};

	void Update() override;
	void Render() const override;
	void Jump();

	void SetAnimationState( AnimationState state );
	void SetCanMove( bool move ) { m_CanMove = move; };
	void SetPyramidPosition( const int x, const int y );
	int GetRow() const { return m_Row; }
	int GetCol() const { return m_Col; }

	void Mirror( bool mirror ) { m_pTextureCoily->Mirror( mirror ); }
	void Moved( SingleMovementComponent::Direction dir );
	bool IsAlive() const { return m_IsAlive; }
private:
	int GetRowStartIndex( int col ) const;
	int GetRowEndIndex( int col ) const;

	const float m_FrameTime = 0.5f;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureCoily;

	AnimationState m_CurrentState = AnimationState::front;

	std::shared_ptr<SingleMovementComponent> m_pSingleMovenment;
	PyramidCubes* m_pPyramid;

	int m_LevelSize;
	int m_Row{ 0 };
	int m_Col{ 1 };
	bool m_IsAlive{true };

	const float m_JumpTime = 3.f;
	float m_Timer = 0.f;

	bool m_CanMove{ true };
	const float m_Speed = 47.f;
	const float m_SpeedBetweenSteps = 0.7f;
};

