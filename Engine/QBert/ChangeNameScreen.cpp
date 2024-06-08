#include "ChangeNameScreen.h"
#include "Commands.h"
#include <ButtonManagerComponent.h>
#include <ButtonComponent.h>
#include "InputBindsManager.h"

ChangeNameScreen::ChangeNameScreen( dae::GameObject* parentGameObject, std::shared_ptr<dae::Texture2D> arrow, std::shared_ptr<dae::Font> font )
    : BaseComponent( parentGameObject )
{
    m_Name = ScoreFile::GetInstance().GetName();
    m_NameText = std::make_shared<dae::TextComponent>( parentGameObject, m_Name, font, true );
    m_NameText->SetLocalPosition( ( 640 - m_NameText->GetTexture()->GetWidth() ) / 2, 50 );
    parentGameObject->AddComponent( m_NameText );

    std::vector<std::shared_ptr<dae::ButtonComponent>> allButtons;

    int columnCount = 0;

    for ( char letter = 'A'; letter <= 'Z'; ++letter )
    {
        m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
        auto myCommand = std::make_shared<AddLetterCommand>( parentGameObject, letter );

        std::string label( 1, letter );
        auto button = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), label, font, myCommand );

        m_Buttons.back()->SetLocalTransform( { m_XOffset, m_YOffset } );
        m_Buttons.back()->AddComponent( button );
        allButtons.push_back( button );

        m_XOffset += m_AddXOffset;
        columnCount++;

        if ( columnCount >= m_MaxColumns ) {
            columnCount = 0;
            m_XOffset = m_StartXOffset;
            m_YOffset += m_AddYOffset;
        }
    }

    m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
    auto pop1 = std::make_shared<RemoveLetterCommand>( parentGameObject );
    auto buttonPop = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Back", font, pop1 );
    m_Buttons.back().get()->SetLocalTransform( { 530, 325 } );
    m_Buttons.back().get()->AddComponent( buttonPop );
    allButtons.push_back( buttonPop );

    m_Buttons.push_back( std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() ) );
    auto clear = std::make_shared<ClearLettersCommand>( parentGameObject );
    auto buttonC = std::make_shared<dae::ButtonComponent>( m_Buttons.back().get(), "Clear", font, clear );
    m_Buttons.back().get()->SetLocalTransform( { 530, 375 } );
    m_Buttons.back().get()->AddComponent( buttonC );
    allButtons.push_back( buttonC );

    m_ButtonsHandeler = std::make_shared<dae::GameObject>( parentGameObject->GetSceneIndex() );
    auto back = std::make_shared<OpenMainMenuCommand>( m_ButtonsHandeler.get() );
    auto buttonB = std::make_shared<dae::ButtonComponent>( m_ButtonsHandeler.get(), "Confirm", font, back );
    m_ButtonsHandeler->SetLocalTransform( { 470, 425 } );
    m_ButtonsHandeler->AddComponent( buttonB );
    allButtons.push_back( buttonB );

    auto buttonManager = std::make_shared<dae::ButtonManagerComponent>( m_ButtonsHandeler.get(), arrow, allButtons );
    m_ButtonsHandeler->AddComponent( buttonManager );

    dae::InputManager::GetInstance().BindActionKeyBoard(
        InputBindsManager::GetInstance().GetKeyboardMenuLeft(),
        InputTypeKeyBoard::IsDownThisFrame,
        dae::PreviousButtonCommand{ m_ButtonsHandeler.get(), 1 }
    );

    dae::InputManager::GetInstance().BindActionKeyBoard(
        InputBindsManager::GetInstance().GetKeyboardMenuRight(),
        InputTypeKeyBoard::IsDownThisFrame,
        dae::NextButtonCommand{ m_ButtonsHandeler.get(), 1 }
    );

    dae::InputManager::GetInstance().BindActionKeyBoard(
        InputBindsManager::GetInstance().GetKeyboardMenuUp(),
        InputTypeKeyBoard::IsDownThisFrame,
        dae::PreviousButtonCommand{ m_ButtonsHandeler.get(), m_MaxColumns }
    );

    dae::InputManager::GetInstance().BindActionKeyBoard(
        InputBindsManager::GetInstance().GetKeyboardMenuDown(),
        InputTypeKeyBoard::IsDownThisFrame,
        dae::NextButtonCommand{ m_ButtonsHandeler.get(), m_MaxColumns }
    );

    dae::InputManager::GetInstance().BindActionKeyBoard(
        InputBindsManager::GetInstance().GetKeyboardMenuSelect(),
        InputTypeKeyBoard::IsDownThisFrame,
        dae::PressButtonCommand{ m_ButtonsHandeler.get() }
    );
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

void ChangeNameScreen::AssignControllerInput()
{
    for ( int index = 0; index < dae::InputManager::GetInstance().GetHowManyControllersConnected(); ++index )
    {
        dae::InputManager::GetInstance().BindActionGamePad( index, XINPUT_GAMEPAD_DPAD_LEFT, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),1 } );
        dae::InputManager::GetInstance().BindActionGamePad( index, XINPUT_GAMEPAD_DPAD_RIGHT, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),1 } );
        dae::InputManager::GetInstance().BindActionGamePad( index, XINPUT_GAMEPAD_DPAD_UP, InputTypeGamePad::IsUpThisFrame, dae::PreviousButtonCommand{ m_ButtonsHandeler.get(),m_MaxColumns } );
        dae::InputManager::GetInstance().BindActionGamePad( index, XINPUT_GAMEPAD_DPAD_DOWN, InputTypeGamePad::IsUpThisFrame, dae::NextButtonCommand{ m_ButtonsHandeler.get(),m_MaxColumns } );
        dae::InputManager::GetInstance().BindActionGamePad( index, XINPUT_GAMEPAD_A, InputTypeGamePad::IsUpThisFrame, dae::PressButtonCommand{ m_ButtonsHandeler.get() } );
    }
}
