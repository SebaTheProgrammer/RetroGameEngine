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
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared < dae::TextureComponent>("background.tga");
	go->AddComponent(texture);
	texture->SetParent(go);

	auto rotate1 = std::make_shared<dae::TransformCircleComponent>();
	rotate1->SetRadius( 1 );
	rotate1->SetSpeed( 3 );
	rotate1->SetDirection( false );
	rotate1->SetParent( go );
	go->AddComponent( rotate1 );
	
	//scene.Add(go);

	auto go2 = std::make_shared<dae::GameObject>();
	texture = std::make_shared < dae::TextureComponent>( "logo.tga" );
	go2->AddComponent( texture );
	texture->SetParent( go2 );

	//auto rotate = std::make_shared<dae::TransformCircleComponent>();
	//rotate->SetRadius( 1 );
	//rotate->SetSpeed( 3 );
	//rotate->SetDirection( true );
	//rotate->SetParent( go2 );
	//go2->AddComponent( rotate );

	go2->SetPosition(216, 180);
	go2->AddChild(go);
	scene.Add(go2);

	go = std::make_shared<dae::GameObject>();
	auto component2 = std::make_shared < dae::FPSComponent>();
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