#include "MainMenuScreen.h"
#include "Commands.h"
#include <ButtonComponent.h>
#include <ButtonManagerComponent.h>

MainMenuScreen::MainMenuScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font, HighScoreScreen* score, int max ) :
	BaseComponent( parentGameObject )
{
	auto texture = std::make_shared < dae::TextureComponent>( parentGameObject, "background.tga" );
	auto title = std::make_shared < dae::TextureComponent>( parentGameObject, "Game Title.png" );
	title->SetLocalPosition( 80, 10 );
	parentGameObject->AddComponent( texture );
	parentGameObject->AddComponent( title );

	//buttons
	m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	std::shared_ptr<dae::Command> changeNameCommand = std::make_shared< OpenSceneWithIndex>( m_Buttons.back().get(), max );
	auto buttonChangeName = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Player: " + ScoreFile::GetInstance().GetName(), font, changeNameCommand );
	m_Buttons.back().get()->SetLocalTransform( { ( 640 - buttonChangeName->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 185 } );
	m_Buttons.back().get()->AddComponent( buttonChangeName );

	m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	std::shared_ptr<dae::Command> myCommand = std::make_shared< SinglePlayer>( m_Buttons.back().get() );
	auto button = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Solo", font, myCommand );
	m_Buttons.back().get()->SetLocalTransform( { ( 640 - button->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 250 } );
	m_Buttons.back().get()->AddComponent( button );

	m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	std::shared_ptr<dae::Command> myCommand2 = std::make_shared< MultiplayerCommand>( m_Buttons.back().get() );
	auto button2 = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Two players", font, myCommand2 );
	m_Buttons.back().get()->SetLocalTransform( { ( 640 - button2->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 300 } );
	m_Buttons.back().get()->AddComponent( button2 );

	m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	std::shared_ptr<dae::Command> myCommand3 = std::make_shared<VersusCommand>( m_Buttons.back().get() );
	auto button3 = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Versus", font, myCommand3 );
	m_Buttons.back().get()->SetLocalTransform( { ( 640 - button3->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 350 } );
	m_Buttons.back().get()->AddComponent( button3 );

	m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
	std::shared_ptr<dae::Command> myCommand4 = std::make_shared< OpenHighScoreCommand>( m_Buttons.back().get(), max-1, score );
	auto button4 = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Highscores", font, myCommand4 );
	m_Buttons.back().get()->SetLocalTransform( { 225, 400 } );
	m_Buttons.back().get()->AddComponent( button4 );

	//ButtonSwitching
	m_ButtonsHandeler = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
	std::vector<std::shared_ptr<dae::ButtonComponent>> allButtons = { buttonChangeName, button, button2, button3, button4 };
	auto buttonManager = std::make_shared<dae::ButtonManagerComponent>( m_ButtonsHandeler.get(), arrow, allButtons );
	m_ButtonsHandeler->AddComponent( buttonManager );

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsDownThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get() ,1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsDownThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get() ,1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_SPACE, InputTypeKeyBoard::IsDownThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );

	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),1 } );
	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),1 } );
	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
}

void MainMenuScreen::Update()
{
	m_Buttons[0]->GetComponent<dae::ButtonComponent>()->GetTextComponent()->SetText( "Player: " + ScoreFile::GetInstance().GetName() );
	m_Buttons[0]->SetLocalTransform({( 640 - m_Buttons[ 0 ]->GetComponent<dae::ButtonComponent>()->GetTextComponent()->GetTexture()->GetWidth() ) / 2, 185});

	for ( auto button : m_Buttons )
	{
		button->Update();
	}

	m_ButtonsHandeler->Update();
}

void MainMenuScreen::Render() const
{
	for ( auto button : m_Buttons )
	{
		button->Render();
	}

	m_ButtonsHandeler->Render();
}
