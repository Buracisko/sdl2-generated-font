#ifndef SPRITE_FONT_H
#define SPRITE_FONT_H

#include <stdlib.h>

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

SDL_Texture* createCustomTexture(SDL_Renderer* renderer);

#endif