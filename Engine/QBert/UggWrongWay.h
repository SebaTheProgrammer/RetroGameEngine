#pragma once
#include "BaseComponent.h"
#include "GameActor.h"
#include "PyramidCubes.h"

class UggWrongWay : public dae::BaseComponent, public dae::GameActor
{
	//i know i did a lot of copy and paste instead of a base class, but it needs to be fast for now.

	public:
	UggWrongWay( dae::GameObject* parentGameObject,
				std::shared_ptr<dae::Texture2D> textureUggWrongWay, int levelSize, PyramidCubes* pyramid );
	~UggWrongWay() = default;
	UggWrongWay( const UggWrongWay& other ) = delete;
	UggWrongWay( UggWrongWay&& other ) = delete;
	UggWrongWay& operator=( const UggWrongWay& other ) = delete;
	UggWrongWay& operator=( UggWrongWay&& other ) = delete;

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

	void Mirror( bool mirror ) { m_pTextureUggWrongWay->Mirror( mirror ); }
	void Moved( SingleMovementComponent::Direction dir );
	bool IsAlive() const { return m_IsAlive; }

private:
	int GetRowStartIndex( int col ) const;
	int GetRowEndIndex( int col ) const;
	void SetStartPos();

	const float m_FrameTime = 0.5f;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureUggWrongWay;

	AnimationState m_CurrentState = AnimationState::front;

	std::shared_ptr<SingleMovementComponent> m_pSingleMovenment;
	PyramidCubes* m_pPyramid;

	int m_LevelSize;
	int m_Row{ 0 };
	int m_Col{ 1 };
	bool m_IsAlive{true };

	const float m_JumpTime = 3.f;
	float m_Timer = 0.f;

	bool m_IsInLeftCorner{ false };
	bool m_IsGoingUp{ false };
	bool m_Up{ true };
	bool m_SettetStartPos{ false };
	bool m_CanMove{ true };
	const float m_Speed = 47.f;
	const float m_SpeedBetweenSteps = 0.7f;
};

