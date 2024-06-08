#pragma once
#include "Singleton.h"
#include "InputManager.h"

class InputBindsManager final
{
public:
	static InputBindsManager& GetInstance()
	{
		static InputBindsManager instance{};
		return instance;
	}

	InputBindsManager(const InputBindsManager& other) = delete;
	InputBindsManager(InputBindsManager&& other) = delete;
	InputBindsManager& operator=(const InputBindsManager& other) = delete;
	InputBindsManager& operator=(InputBindsManager&& other) = delete;

	//Controller Menu
	int GetControllerMenuUp() const { return GAMEPAD_DPAD_UP; }
	int GetControllerMenuDown() const { return GAMEPAD_DPAD_DOWN; }
	int GetControllerMenuLeft() const { return GAMEPAD_DPAD_LEFT; }
	int GetControllerMenuRight() const { return GAMEPAD_DPAD_RIGHT; }
	int GetControllerMenuSelect() const { return GAMEPAD_A; }

	//Controller Game
	int GetControllerGameUp() const { return GAMEPAD_DPAD_UP; }
	int GetControllerGameDown() const { return GAMEPAD_DPAD_DOWN; }
	int GetControllerGameLeft() const { return GAMEPAD_DPAD_LEFT; }
	int GetControllerGameRight() const { return GAMEPAD_DPAD_RIGHT; }

	//Keyboard Menu
	SDL_Scancode GetKeyboardMenuUp() const { return SDL_SCANCODE_W; }
	SDL_Scancode GetKeyboardMenuDown() const { return SDL_SCANCODE_S; }
	SDL_Scancode GetKeyboardMenuLeft() const { return SDL_SCANCODE_A; }
	SDL_Scancode GetKeyboardMenuRight() const { return SDL_SCANCODE_D; }
	SDL_Scancode GetKeyboardMenuSelect() const { return SDL_SCANCODE_SPACE; }

	//Keyboard Game
	SDL_Scancode GetKeyboardGameUp() const { return SDL_SCANCODE_W; }
	SDL_Scancode GetKeyboardGameDown() const { return SDL_SCANCODE_S; }
	SDL_Scancode GetKeyboardGameLeft() const { return SDL_SCANCODE_A; }
	SDL_Scancode GetKeyboardGameRight() const { return SDL_SCANCODE_D; }

private:
	InputBindsManager() = default;
};