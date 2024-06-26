#pragma once
#include <SDL.h>
#include <memory>
#include "InputCommands.h"

enum class InputTypeGamePad
{
	IsPressed,
	IsDownThisFrame,
	IsUpThisFrame
};

struct InputBindingGamePad
{
	int wichPlayer;
	int key;
	InputTypeGamePad inputType;
	std::shared_ptr<dae::Command> command;

	template<typename CommandType>
	InputBindingGamePad( int wichplayer, int keyIn, InputTypeGamePad inputTypeIn, CommandType commandIn )
		:
		wichPlayer{ wichplayer },
		key{ keyIn }
		, inputType{ inputTypeIn }
	{
		command = std::make_shared<CommandType>( commandIn );
	}
};

enum class InputTypeKeyBoard
{
	IsPressed,
	IsDownThisFrame,
	IsUpThisFrame
};

struct InputBindingKeyBoard
{
	SDL_Scancode key;
	InputTypeKeyBoard inputType;
	std::shared_ptr<dae::Command> command;

	template<typename CommandType>
	InputBindingKeyBoard( SDL_Scancode keyIn, InputTypeKeyBoard inputTypeIn, CommandType commandIn )
		: key{ keyIn },
		inputType{ inputTypeIn }
	{
		command = std::make_shared<CommandType>( commandIn );
	}
};