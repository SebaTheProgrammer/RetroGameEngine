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

		void SetRows( int rows ) { m_Rows = rows; }
		void SetColumns( int columns ) { m_Columns = columns; }
		void SetCurrentRow( int row ) { m_CurrentRow = row; }
		void SetCurrentColumn( int column ) { m_CurrentColumn = column; }
		void SetMaxRows( int rows ) { m_MaxRows = rows; }
		void SetMaxColumns( int columns ) { m_MaxColumns = columns; }
		void SetMinRows( int rows ) { m_MinRows = rows; }
		void SetMinColumns( int columns ) { m_MinColumns = columns; }

	private:
		std::shared_ptr<dae::Texture2D> m_pTexture;
		int m_Rows;
		int m_Columns;
		float m_FrameTime;
		int m_MaxRows;
		int m_MaxColumns;
		int m_MinRows{ 0 };
		int m_MinColumns{ 0 };

		int m_CurrentRow;
		int m_CurrentColumn;
		float m_AccumulatedTime;

		float m_X;
		float m_Y;

		float m_Scale;

		bool m_Mirror = false;
	};
}

