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
#include "TransformCircleComponent.h"
#include "ResourceManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//bg
	auto go = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared < dae::TextureComponent>( go.get(), "background.tga");
	go->AddComponent(texture);
	scene.Add( go );

	//logo
	auto go2 = std::make_shared<dae::GameObject>();
	texture = std::make_shared < dae::TextureComponent>(go2.get(), "logo.tga" );
	go2->AddComponent( texture );
	go2->SetLocalTransform( 216, 180, 0 );
	scene.Add(go2);

	//fps counter
	auto font = dae::ResourceManager::GetInstance().LoadFont( "Lingua.otf", 36 );
	auto go3 = std::make_shared<dae::GameObject>();
	go3->AddComponent( std::make_shared<dae::FPSComponent>( go3.get(), "0 FPS", font ) );
	go3->SetLocalTransform( 80, 10, 0 );
	scene.Add( go3 );

	// Pacman anchor
	auto anchor = std::make_shared<dae::GameObject>();
	anchor->SetLocalTransform( 216, 180, 0 );
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}