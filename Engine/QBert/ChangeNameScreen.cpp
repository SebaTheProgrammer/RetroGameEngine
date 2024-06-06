#include "ChangeNameScreen.h"
#include "Commands.h"
#include <ButtonManagerComponent.h>
#include <ButtonComponent.h>

ChangeNameScreen::ChangeNameScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font )
	: BaseComponent( parentGameObject )
{
	m_Name = ScoreFile::GetInstance().GetName();
	m_NameText = std::make_shared<dae::TextComponent>( parentGameObject, m_Name, font, true );
	m_NameText->SetLocalPosition( ( 640 - m_NameText->GetTexture()->GetWidth() ) / 2, 50 );
	parentGameObject->AddComponent( m_NameText );

	std::vector<std::shared_ptr<dae::ButtonComponent>> allButtons;

    float xOffset = 150.0f;
    float yOffset = 150.0f;
    int columnCount = 0;
    const int maxColumns = 9;

    for ( char letter = 'A'; letter <= 'Z'; ++letter ) 
    {
        m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
        auto myCommand = std::make_shared<AddLetterCommand>( parentGameObject, letter );

        std::string label( 1, letter );
        auto button = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), label, font, myCommand );

        m_Buttons.back()->SetLocalTransform( { xOffset, yOffset } );
        m_Buttons.back()->AddComponent( button );
        allButtons.push_back( button );

        xOffset += 45.0f;
        columnCount++;

        if ( columnCount >= maxColumns ) {
            columnCount = 0;
            xOffset = 150.0f;
            yOffset += 45.0f;
        }
    }

    m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
    auto clear = std::make_shared<ClearLettersCommand>( parentGameObject );
    auto buttonC = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Clear", font, clear );
    m_Buttons.back().get()->SetLocalTransform( { 530, 375 } );
    m_Buttons.back().get()->AddComponent( buttonC );
    allButtons.push_back( buttonC );

    m_ButtonsHandeler = std::make_shared<dae::GameObject>(parentGameObject->GetSceneIndex());
    auto back = std::make_shared<OpenMainMenuCommand>(m_ButtonsHandeler.get());
    auto buttonB = std::make_shared<dae::ButtonComponent>(m_ButtonsHandeler.get(), "Back", font, back);
    m_ButtonsHandeler->SetLocalTransform({ 530, 425});
    m_ButtonsHandeler->AddComponent(buttonB);
    allButtons.push_back(buttonB);

    auto buttonManager = std::make_shared<dae::ButtonManagerComponent>(m_ButtonsHandeler.get(), arrow, allButtons);
    m_ButtonsHandeler->AddComponent(buttonManager);

	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_A, InputTypeKeyBoard::IsDownThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),1 } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_D, InputTypeKeyBoard::IsDownThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),1 } );
    dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_W, InputTypeKeyBoard::IsDownThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(), maxColumns } );
    dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_S, InputTypeKeyBoard::IsDownThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),maxColumns } );
	dae::InputManager::GetInstance().BindActionKeyBoard( SDL_SCANCODE_SPACE, InputTypeKeyBoard::IsDownThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );

	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),1 } );
	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),1 } );
    dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),maxColumns } );
    dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),maxColumns } );
	dae::InputManager::GetInstance().BindActionGamePad(XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
}

void ChangeNameScreen::Update()
{
	for ( auto button : m_Buttons )
	{
		button->Update();
	}

	m_ButtonsHandeler->Update();
}

void ChangeNameScreen::Render() const
{
	for ( auto button : m_Buttons )
	{
		button->Render();
	}

	m_ButtonsHandeler->Render();
	m_NameText->Render();
}

void ChangeNameScreen::SetName( std::string name )
{
	m_Name = name;
	m_NameText->SetText(m_Name );
	ScoreFile::GetInstance().SetName( name );

    m_NameText->SetLocalPosition( ( 640 - m_NameText->GetTexture()->GetWidth() ) / 2, 50 );
}
