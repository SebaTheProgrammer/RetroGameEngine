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
		void BindActionKeyBoard( SDL_Scancode key, CommandType command )
		{
			InputBindingKeyBoard inputBinding{ key, command };
			m_InputBindingsKeyBoard.emplace_back( inputBinding );
		}

	private:

		std::vector<InputBindingGamePad> m_InputBindingsGamePad{};
		std::vector<InputBindingKeyBoard> m_InputBindingsKeyBoard{};

		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousState{};

		int m_ButtonsPressedThisFrame{};
		int m_ButtonsReleasedThisFrame{};

		bool IsDownThisFrame( unsigned int button ) const;
		bool IsUpThisFrame( unsigned int button ) const;
		bool IsPressed( unsigned int button ) const;
	};

}
