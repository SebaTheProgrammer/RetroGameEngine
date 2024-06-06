#pragma once
#include "BaseComponent.h"
#include <TextComponent.h>
#include <TextureComponent.h>
#include "ScoreFile.h"

class ChangeNameScreen : public dae::BaseComponent
{
	public:
	ChangeNameScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> texture, std::shared_ptr<dae::Font> font );
	virtual ~ChangeNameScreen() = default;

	void Update() override;
	void Render() const override;

	void SetName( std::string name ) { ScoreFile::GetInstance().SetName( name ); };
	std::string GetName() const { return  ScoreFile::GetInstance().GetName(); };

	private:

};

