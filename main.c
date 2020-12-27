#include <stdio.h>
#include <stdlib.h>

// Needded to deal with windows main function linking
#define SDL_MAIN_HANDLED

#include "SDL.h"

int main(int argc, char* argv[])
{
	// Args will be used in the future
	for (int i = 0; i < argc; ++i)
		printf("arg[%d]: %s\n", i, argv[i]);
	// Needded to deal with windows main function linking.
	SDL_SetMainReady();

	// SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// Cleanup and exit
	SDL_Quit();

	return 0;
}
