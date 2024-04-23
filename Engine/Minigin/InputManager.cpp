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
	m_ButtonsPressedThisFrameGP = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrameGP = buttonChanges & ( ~m_CurrentState.Gamepad.wButtons );

	//Keyboard input handling
	const uint8_t* pKeyboardState = SDL_GetKeyboardState( nullptr );

	const uint8_t* currentKeyboardState = SDL_GetKeyboardState( NULL );
	memcpy( m_PreviousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES );

	for ( auto& inputBinding : m_InputBindingsKeyBoard )
	{
		if ( !inputBinding.command )
			continue;

		if ( pKeyboardState[ inputBinding.key ] )
		{
			inputBinding.command->Execute();
		}

		/*switch ( inputBinding.inputType )
		{
		case InputTypeKeyBoard::IsPressed:
		{
			if ( IsPressedKB( inputBinding.key ) )
			{
				
			}
		}
		case InputTypeKeyBoard::IsDownThisFrame:
		{
			if ( IsDownThisFrameKB( inputBinding.key ) )
			{
				if ( pKeyboardState[ inputBinding.key ] )
				{
					inputBinding.command->Execute();
				}
			}
			break;
		}
		case InputTypeKeyBoard::IsUpThisFrame:
		{
			if ( IsUpThisFrameKB( inputBinding.key ) )
			{
				if ( pKeyboardState[ inputBinding.key ] )
				{
					inputBinding.command->Execute();
				}
			}
			break;
		}*/
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
			if ( IsPressedGP( inputBinding.key ) )
			{
				inputBinding.command->Execute();
			}
			break;
		}
		case InputTypeGamePad::IsDownThisFrame:
		{
			if ( IsDownThisFrameGP( inputBinding.key ) )
			{
				inputBinding.command->Execute();
			}
			break;
		}
		case InputTypeGamePad::IsUpThisFrame:
		{
			if ( IsUpThisFrameGP( inputBinding.key ) )
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

bool dae::InputManager::IsDownThisFrameGP( unsigned int button ) const
{
	return m_ButtonsPressedThisFrameGP & button;
}
bool dae::InputManager::IsUpThisFrameGP( unsigned int button ) const
{
	return m_ButtonsReleasedThisFrameGP & button;
}
bool dae::InputManager::IsPressedGP( unsigned int button ) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

bool dae::InputManager::IsPressedKB( unsigned int key ) const
{
	return SDL_GetKeyboardState( NULL )[ key ] != 0;
}
bool dae::InputManager::IsDownThisFrameKB( unsigned int key ) const
{
	return SDL_GetKeyboardState( NULL )[ key ] != 0 && m_PreviousKeyboardState[ key ] == 0;
}

bool dae::InputManager::IsUpThisFrameKB( unsigned int key ) const
{
	return SDL_GetKeyboardState( NULL )[ key ] == 0 && m_PreviousKeyboardState[ key ] != 0;
}
