#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextureComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto texture = new dae::TextureComponent("background.tga");
	go->AddComponent(texture);
	texture->SetParent(go);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	texture = new dae::TextureComponent( "logo.tga" );
	go->AddComponent( texture );
	texture->SetParent( go );
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto component2 = new dae::FPSComponent();
	component2->SetText( "FPS" );
	component2->SetSize( 36 );
	component2->SetFont( "Lingua.otf" );
	component2->SetPosition( 20, 20 );
	go->AddComponent( component2 );
	scene.Add( go );
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}