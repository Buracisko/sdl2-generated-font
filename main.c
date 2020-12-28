#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Needded to deal with windows main function linking
#define SDL_MAIN_HANDLED
#include "SDL.h"

// Window and its properties
const char* g_wTitle = "Generated font test";
const int g_wWidth = 640;
const int g_wHeight = 360;
SDL_Window* g_window;

// Renderer
SDL_Renderer* g_renderer;
SDL_Surface* g_screenSurface;

// Execution handling
bool isRunning = true;

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
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Create window
	g_window = SDL_CreateWindow(
		g_wTitle,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		g_wWidth,
		g_wHeight,
		SDL_WINDOW_OPENGL
	);
	if (!g_window)
	{
		fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
		return 1;
	}
	g_screenSurface = SDL_GetWindowSurface(g_window);

	// Create renderer
	g_renderer = SDL_CreateRenderer(
		g_window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	if (!g_renderer)
	{
		fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
		return 1;
	}

	// Create custom surface
	Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	SDL_Surface *testSurface =
		SDL_CreateRGBSurface(0, 64, 64, 32, rmask, gmask, bmask, amask);
	if (!testSurface)
	{
		fprintf(stderr, "Unable to create RGB surface: %s\n", SDL_GetError());
		return 1;
	}
	//Allocate format from window
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(testSurface->format->format);
	Uint32 targetColor = SDL_MapRGBA(mappingFormat, 0xFF, 0, 0, 0x88);
	Uint32* pixels = (Uint32*)testSurface->pixels;
	int pixelCount = (testSurface->pitch / 4) * testSurface->h;

	// Edit pixel data
    SDL_LockSurface(testSurface);

    for (int i = 0; i < pixelCount; ++i)
		pixels[i] = targetColor;

    SDL_UnlockSurface(testSurface);
	SDL_FreeFormat(mappingFormat);
	
	// Main execution loop
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
		}

		SDL_RenderClear(g_renderer);

		SDL_Rect dest = {32, 32, 64, 64};
		SDL_BlitSurface(testSurface, NULL, g_screenSurface, &dest);
		SDL_UpdateWindowSurface(g_window);

		SDL_RenderPresent(g_renderer);
	}

	// Cleanup and exit
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();

	return 0;
}
