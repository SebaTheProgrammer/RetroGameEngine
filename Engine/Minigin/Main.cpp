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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto component = new dae::TextComponent();
	component->SetText("Programming 4 Assignment");
	component->SetSize( 36 );
	component->SetFont("Lingua.otf");
	go->AddComponent( component );
	go->SetPosition( 80, 20 );
	scene.Add( go );

	go = std::make_shared<dae::GameObject>();
	auto component2 = new dae::FPSComponent();
	component2->SetText( "FPS" );
	component2->SetSize( 36 );
	component2->SetFont( "Lingua.otf" );
	component2->SetPosition( 80, 120 );
	go->AddComponent( component2 );
	scene.Add( go );

	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}