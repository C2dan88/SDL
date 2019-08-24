#ifndef __TEXTURE_CACHE_H
#define __TEXTURE_CACHE_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "types.h"

typedef struct TextureCache {
    SDL_Texture *texture;
    //int index;
    struct TextureCache *next;
} TextureCache;

void InitTextureCache();
void PushTextureCache(SDL_Texture *newTexture);
void DestroryTextureCache(/*struct TextureCache **cache*/);

#endif