#include <SDL.h>
#include "InputManager.h"
#pragma comment(lib, "xinput.lib")

dae::InputManager::InputManager()
{
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while ( SDL_PollEvent( &e ) ) {
		if ( e.type == SDL_QUIT ) {
			return false;
		}
	}

	CopyMemory( &m_PreviousState, &m_CurrentState, sizeof( XINPUT_STATE ) );
	ZeroMemory( &m_CurrentState, sizeof( XINPUT_STATE ) );
	XInputGetState( 0, &m_CurrentState );

	int buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ( ~m_CurrentState.Gamepad.wButtons );

	//Keyboard input handling
	const uint8_t* pKeyboardState = SDL_GetKeyboardState( nullptr );
	for ( auto& inputBinding : m_InputBindingsKeyBoard )
	{
		if ( !inputBinding.command )
			continue;

		if ( pKeyboardState[ inputBinding.key ] )
		{
			inputBinding.command->Execute();
		}
	}

	//Controller input handling
	for ( auto& inputBinding : m_InputBindingsGamePad )
	{
		if ( !inputBinding.command )
			continue;

		switch ( inputBinding.inputType )
		{
		case InputTypeGamePad::IsPressed:
		{
			if ( IsPressed( inputBinding.key ) )
			{
				inputBinding.command->Execute();
			}
			break;
		}
		case InputTypeGamePad::IsDownThisFrame:
		{
			if ( IsDownThisFrame( inputBinding.key ) )
			{
				inputBinding.command->Execute();
			}
			break;
		}
		case InputTypeGamePad::IsUpThisFrame:
		{
			if ( IsUpThisFrame( inputBinding.key ) )
			{
				inputBinding.command->Execute();
			}
			break;
		}
		default:
			break;
		}
	}

	return true;
}

bool dae::InputManager::IsDownThisFrame( unsigned int button ) const
{
	return m_ButtonsPressedThisFrame & button;
}
bool dae::InputManager::IsUpThisFrame( unsigned int button ) const
{
	return m_ButtonsReleasedThisFrame & button;
}
bool dae::InputManager::IsPressed( unsigned int button ) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
