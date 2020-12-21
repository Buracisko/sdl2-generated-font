#include <stdio.h>
#include <stdlib.h>

// Needded to deal with windows main function linking
#define SDL_MAIN_HANDLED

#include "SDL.h"

/*
Compile with:
	gcc -o hello main.c -I/usr/include/SDL2 `sdl2-config --cflags --libs`
*/

void printSDLVersion();

int main(int argc, char* argv[])
{
	// Needded to deal with windows main function linking.
	SDL_SetMainReady();

	// SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	puts("SDL initialized.");

	printSDLVersion();

	// Cleanup and exit
	SDL_Quit();

	return 0;
}

void printSDLVersion()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("Compiled against SDL version %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
	printf("Linking against SDL version %d.%d.%d\n", linked.major, linked.minor, linked.patch);
}
