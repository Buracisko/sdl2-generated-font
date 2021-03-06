#include "spriteFont.h"
#include "SDL.h"

int glyph[GLYPH_HEIGHT][GLYPH_WIDTH] = {
    {1, 1, 0, 0, 1, 1, 0},
    {1, 1, 0, 1, 1, 0, 0},
    {1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 1, 1}
};

SDL_Texture* createCustomTexture(SDL_Renderer* renderer)
{
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
		SDL_CreateRGBSurface(0, GLYPH_WIDTH, GLYPH_HEIGHT, 32, rmask, gmask, bmask, amask);
	if (!testSurface)
	{
		fprintf(stderr, "Unable to create RGB surface: %s\n", SDL_GetError());
		return NULL;
	}
	
	//Allocate format from window
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(testSurface->format->format);
	Uint32 targetColor = SDL_MapRGBA(mappingFormat, 0xFF, 0xFF, 0xFF, 0xFF);
	Uint32* pixels = (Uint32*)testSurface->pixels;
	int pixelCount = (testSurface->pitch / 4) * testSurface->h;

	// Edit pixel data
    SDL_LockSurface(testSurface);

    for (int i = 0; i < pixelCount; ++i)
    {
        int row = i / testSurface->w;
        int col = i % testSurface->w;
        if (glyph[row][col] == 1)
            pixels[i] = targetColor;
    }

    SDL_UnlockSurface(testSurface);
	SDL_FreeFormat(mappingFormat);

	SDL_Texture* resultingTexture = SDL_CreateTextureFromSurface(renderer, testSurface);
	SDL_FreeSurface(testSurface);
	return resultingTexture;
}