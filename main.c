#include "spriteFont.h"

// Needded to deal with windows main function linking
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

	SDL_Texture* customTexture = createCustomTexture(g_renderer);

	// Main execution loop
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
		}

		SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(g_renderer);
		
		int yOffset = 4;
		int xOffset = 4;
		for (int i = 64; i > 0; i -= 8)
		{
			SDL_Rect dest = {xOffset, yOffset, i, i};
			SDL_RenderCopy(g_renderer, customTexture, NULL, &dest);
			yOffset += dest.h + 4;
		}
		/*
		SDL_Rect dest = {4, 4, GLYPH_WIDTH * 4, GLYPH_HEIGHT * 4};
		SDL_RenderCopy(g_renderer, customTexture, NULL, &dest);

		SDL_Rect dest2 = {4, 4 + dest.y + dest.h, GLYPH_WIDTH * 2, GLYPH_HEIGHT * 2};
		SDL_RenderCopy(g_renderer, customTexture, NULL, &dest2);

		SDL_Rect dest3 = {4, 4 + dest2.y + dest2.h, GLYPH_WIDTH, GLYPH_HEIGHT};
		SDL_RenderCopy(g_renderer, customTexture, NULL, &dest3);

		SDL_Rect dest4 = {4, 4 + dest3.y + dest3.h, 14, 14};
		SDL_RenderCopy(g_renderer, customTexture, NULL, &dest4);
		*/
		SDL_RenderPresent(g_renderer);
	}

	// Cleanup and exit
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();

	return 0;
}
