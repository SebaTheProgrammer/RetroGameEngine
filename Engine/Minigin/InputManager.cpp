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
	XInputGetState( 1, &m_CurrentState );

	int buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrameGP = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrameGP = buttonChanges & ( ~m_CurrentState.Gamepad.wButtons );

	//Keyboard input handling
	const uint8_t* pKeyboardState = SDL_GetKeyboardState( nullptr );

	const uint8_t* currentKeyboardState = SDL_GetKeyboardState( NULL );

	for ( auto& inputBinding : m_InputBindingsKeyBoard )
	{
		if ( !inputBinding.command )
			continue;

		switch ( inputBinding.inputType )
		{
		case InputTypeKeyBoard::IsPressed:
		{
			if ( IsPressedKB( inputBinding.key ) )
			{
				if ( pKeyboardState[ inputBinding.key ] )
				{
					inputBinding.command->Execute();
				}
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
		}
		}
	}

	//Controller input handling
	XINPUT_STATE controllerState0;
	XINPUT_STATE controllerState1;
	for ( auto& inputBinding : m_InputBindingsGamePad )
	{
		if ( !inputBinding.command )
			continue;

		if ( XInputGetState( 0, &controllerState0 ) == ERROR_SUCCESS ) {
			CheckInputBinding( inputBinding, controllerState0, 0 );
		}
		else if ( XInputGetState( 1, &controllerState1 ) == ERROR_SUCCESS ) {
			CheckInputBinding( inputBinding, controllerState1, 1 );
		}
	}

	memcpy( m_PreviousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES );
	return true;
}

void dae::InputManager::CheckInputBinding( InputBindingGamePad inputBinding, XINPUT_STATE controllerState, int controllerIndex ) {
	if ( inputBinding.wichPlayer != controllerIndex ) {
		return;
	}

	switch ( inputBinding.inputType ) {
	case InputTypeGamePad::IsPressed:
		if ( IsPressedGP( inputBinding.key ) && ( controllerState.Gamepad.wButtons & inputBinding.key ) && inputBinding.command !=nullptr) {
			inputBinding.command->Execute();
		}
		break;
	case InputTypeGamePad::IsDownThisFrame:
		if ( IsDownThisFrameGP( inputBinding.key ) && ( controllerState.Gamepad.wButtons & inputBinding.key && inputBinding.command != nullptr ) ) {
			inputBinding.command->Execute();
		}
		break;
	case InputTypeGamePad::IsUpThisFrame:
		if ( IsUpThisFrameGP( inputBinding.key ) && !( controllerState.Gamepad.wButtons & inputBinding.key && inputBinding.command != nullptr ) ) {
			inputBinding.command->Execute();
		}
		break;
	default:
		break;
	}
}

int dae::InputManager::GetHowManyControllersConnected()
{
	int connectedControllers = 0;

	for ( DWORD i = 0; i < XUSER_MAX_COUNT; ++i ) {
		XINPUT_STATE state;
		ZeroMemory( &state, sizeof( XINPUT_STATE ) );

		DWORD result = XInputGetState( i, &state );

		if ( result == ERROR_SUCCESS ) {
			++connectedControllers;
		}
	}

	return connectedControllers;
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
