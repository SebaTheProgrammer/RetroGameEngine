#pragma once

#include <Xinput.h>
#include <minwinbase.h>

class Controller
{
public:
    Controller( int index ) : m_Index( index )
    {
        ZeroMemory( &m_CurrentState, sizeof( XINPUT_STATE ) );
        ZeroMemory( &m_PreviousState, sizeof( XINPUT_STATE ) );
    }

    void Update()
    {
        CopyMemory( &m_PreviousState, &m_CurrentState, sizeof( XINPUT_STATE ) );
        ZeroMemory( &m_CurrentState, sizeof( XINPUT_STATE ) );

        XInputGetState( m_Index, &m_CurrentState );

        int buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
        m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
        m_ButtonsReleasedThisFrame = buttonChanges & ( ~m_CurrentState.Gamepad.wButtons );
    }

    bool IsDownThisFrame( unsigned int button ) const
    {
        return m_ButtonsPressedThisFrame & button;
    }

    bool IsUpThisFrame( unsigned int button ) const
    {
        return m_ButtonsReleasedThisFrame & button;
    }

    bool IsPressed( unsigned int button ) const
    {
        return m_CurrentState.Gamepad.wButtons & button;
    }

private:
    int m_Index;
    XINPUT_STATE m_CurrentState;
    XINPUT_STATE m_PreviousState;
    int m_ButtonsPressedThisFrame;
    int m_ButtonsReleasedThisFrame;
};
