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
	int key;

	InputTypeGamePad inputType;
	std::shared_ptr<dae::Command> command;

	template<typename CommandType>
	InputBindingGamePad( int keyIn, InputTypeGamePad inputTypeIn, CommandType commandIn )
		: key{ keyIn }
		, inputType{ inputTypeIn }
	{
		command = std::make_shared<CommandType>( commandIn );
	}
};

struct InputBindingKeyBoard
{
	SDL_Scancode key;
	std::shared_ptr<dae::Command> command;

	template<typename CommandType>
	InputBindingKeyBoard( SDL_Scancode keyIn, CommandType commandIn )
		: key{ keyIn }
	{
		command = std::make_shared<CommandType>( commandIn );
	}
};