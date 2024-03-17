#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform() = default;
		Transform( float x, float y, float z = 0.f ) { m_Position = { x, y, z }; }
		Transform( glm::vec3 position ) { m_Position = position; }
		Transform( glm::vec2 positionXY, float positionZ = 0.f ) { m_Position = { positionXY, positionZ }; }

		~Transform() = default;
		Transform( const Transform& other ) = default;
		Transform( Transform&& other ) = default;
		Transform& operator=( const Transform& other ) = default;
		Transform& operator=( Transform&& other ) = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	
		Transform operator+( Transform other )
		{
			glm::vec3 newPos{ m_Position + other.GetPosition() };

			return Transform{ newPos };
		}
		Transform operator+=( Transform other )
		{
			m_Position += other.GetPosition();

			return Transform{ m_Position };
		}

		Transform operator-( Transform other )
		{
			glm::vec3 newPos{ m_Position - other.GetPosition() };

			return Transform{ newPos };
		}
		Transform operator-=( Transform other )
		{
			m_Position -= other.GetPosition();

			return Transform{ m_Position };
		}
	
	private:
		glm::vec3 m_Position;
	};
}
