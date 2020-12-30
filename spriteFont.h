#ifndef SPRITE_FONT_H
#define SPRITE_FONT_H

#include <stdlib.h>

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 8

extern const char* aGlyph;

typedef struct SpriteFont
{
    SDL_Texture* sheet;
    int height;
    int width;
} SpriteFont;

// TODO: Move inside - not a public API
SDL_Texture* createCustomTexture(SDL_Renderer* renderer);

SpriteFont createSpriteFont(int height, SDL_Renderer* renderer);

void destroySpriteFont(SpriteFont* font);

#endif