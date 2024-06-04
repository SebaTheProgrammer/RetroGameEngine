#pragma once
#include "BaseComponent.h"
#include "GameActor.h"
#include <AnimatedTextureComponent.h>
#include "SingleMovementComponent.h"

class FloatingDisc : public dae::BaseComponent, public dae::GameActor
{
public:

	FloatingDisc( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> textureDisc, int levelSize, bool isLeftDisc );
	~FloatingDisc() = default;

	FloatingDisc( const FloatingDisc& other ) = delete;
	FloatingDisc( FloatingDisc&& other ) = delete;
	FloatingDisc& operator=( const FloatingDisc& other ) = delete;
	FloatingDisc& operator=( FloatingDisc&& other ) = delete;

	void Update() override;
	void Render() const override;

	void FloatToTop();

	void SetCanMove( bool move ) { m_CanMove = move; };
	void SetPyramidPosition( const int x, const int y );
	int GetRow() const { return m_Row; }
	int GetCol() const { return m_Col; }

	void ResetPosition();
	int GetRowStartIndex( int col )const;
	int GetRowEndIndex( int col ) const;

private:
	const float m_FrameTime = 0.5f;
	std::shared_ptr<dae::AnimatedTextureComponent> m_pTextureDisc;
	std::shared_ptr <SingleMovementComponent> m_pSingleMovenment;
	glm::vec2 m_Direction;
	glm::vec2 m_Offset{15, -20};

	int m_LevelSize;
	int m_Row{ 0 };
	int m_Col{ 1 };

	bool m_SettetStartPos = false;
	bool m_IsLeftDisc;
	bool m_CanMove = false;
	float m_StepSize{ 1.2f };
	const float m_Speed = 47.f;
	const float m_SpeedBetweenSteps = 0.7f;
};

