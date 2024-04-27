#pragma once
#include "BaseComponent.h"
#include <GameObject.h>
class Cube;

class PyramidCubes : public dae::BaseComponent
{
public:
	PyramidCubes( dae::GameObject* parentGameObject, int size, int wichLevel);
	virtual ~PyramidCubes()= default;

	PyramidCubes( const PyramidCubes& other ) = delete;
	PyramidCubes( PyramidCubes&& other ) = delete;
	PyramidCubes& operator=( const PyramidCubes& other ) = delete;
	PyramidCubes& operator=( PyramidCubes&& other ) = delete;

	void SetScaleSize( int size ) { m_Size = size; SetLevel( m_WhichLevel ); }
	void SetWhichLevel(int whichLevel){ m_WhichLevel = whichLevel; }

	void Update() override;
	void Render() const override;

	void SetLevel( const int level);
	void SetScale( float scale ){ m_Scale = scale; }

	void CompleteLevel();

private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	int m_Size;
	int m_WhichLevel;

	std::vector<std::shared_ptr<Cube>> m_pCubes;

	float m_Scale = 1.5f;
};
