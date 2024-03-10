#include <SDL.h>
#include "InputManager.h"
#include "../3rdParty/imgui_impl_sdl2.h"

bool dae::InputManager::ProcessInput()
{
	//ZeroMemory( &m_CurrentState, sizeof( XINPUT_STATE ) );
	//XInputGetState( 0, &m_CurrentState );

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		//proces event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);

		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	return true;
}
