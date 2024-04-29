#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class AnimatedTextureComponent : public BaseComponent
	{
		public:
		AnimatedTextureComponent( GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, float scale, int rows, int columns, int currentColumn, float frameTime = 0 );
		virtual ~AnimatedTextureComponent() = default;

		AnimatedTextureComponent( const AnimatedTextureComponent& other ) = delete;
		AnimatedTextureComponent( AnimatedTextureComponent&& other ) = delete;
		AnimatedTextureComponent& operator=( const AnimatedTextureComponent& other ) = delete;
		AnimatedTextureComponent& operator=( AnimatedTextureComponent&& other ) = delete;

		void Update() override;
		void Render() const override;

		void Animate( float frameTime ) { m_FrameTime = frameTime; }

		void NextFrame();
		void Reset();

		void Mirror( bool mirror ) { m_Mirror = mirror; }

	private:
		std::shared_ptr<dae::Texture2D> m_pTexture;
		int m_Rows;
		int m_Columns;
		float m_FrameTime;
		int m_ActiveRows;
		int m_ActiveColumns;

		int m_CurrentRow;
		int m_CurrentColumn;
		float m_AccumulatedTime;

		float m_X;
		float m_Y;

		float m_Scale;

		bool m_Mirror = false;
		bool m_StandStill = false;
	};
}

