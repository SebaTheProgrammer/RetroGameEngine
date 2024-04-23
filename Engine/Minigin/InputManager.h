#pragma once
#include "Singleton.h"

#include <Windows.h>
#include <Xinput.h>
#include <memory>
#include <type_traits>
#include <WinUser.h>

#include "InputCommands.h"
#include "InputStructs.h"
#include <vector>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager();
		~InputManager() = default;
		InputManager( const InputManager& other ) = delete;
		InputManager( InputManager&& other ) = delete;
		InputManager& operator=( const InputManager& other ) = delete;
		InputManager& operator=( InputManager&& other ) = delete;

		bool ProcessInput();

		template<typename CommandType>
		void BindActionGamePad( int key, InputTypeGamePad inputType, CommandType command )
		{
			InputBindingGamePad inputBinding{ key, inputType, command };
			m_InputBindingsGamePad.emplace_back( inputBinding );
		}

		template<typename CommandType>
		void BindActionKeyBoard( SDL_Scancode key, CommandType command )// InputTypeKeyBoard inputType
		{
			InputBindingKeyBoard inputBinding{ key, command };//inputType
			m_InputBindingsKeyBoard.emplace_back( inputBinding );
		}

	private:

		std::vector<InputBindingGamePad> m_InputBindingsGamePad{};
		std::vector<InputBindingKeyBoard> m_InputBindingsKeyBoard{};

		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousState{};

		uint8_t m_PreviousKeyboardState[ SDL_NUM_SCANCODES ] = { 0 };

		int m_ButtonsPressedThisFrameGP{};
		int m_ButtonsReleasedThisFrameGP{};

		bool IsDownThisFrameGP( unsigned int button ) const;
		bool IsUpThisFrameGP( unsigned int button ) const;
		bool IsPressedGP( unsigned int button ) const;

		int m_ButtonsPressedThisFrameKB{};
		int m_ButtonsReleasedThisFrameKB{};

		bool IsDownThisFrameKB( unsigned int button ) const;
		bool IsUpThisFrameKB( unsigned int button ) const;
		bool IsPressedKB( unsigned int button ) const;
	};

}
