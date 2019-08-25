#ifndef __TEXTURE_MEMORY
#define __TEXTURE_MEMORY

#include <SDL.h>

#include "types.h"
#include "textureCache.h"

#include "utils.c"

global_variable TextureCache *textureCache;

void InitTextureCache() {
    textureCache = malloc(sizeof(TextureCache));
    textureCache->next = NULL;
}

void PushTextureCache(SDL_Texture *newTexture) {
    struct TextureCache* newTextureCache = malloc(sizeof(struct TextureCache));
  	newTextureCache->texture = newTexture;
  	newTextureCache->next = textureCache;
  	textureCache = newTextureCache;
}

int getCount(struct TextureCache *head) 
{ 
    // Base case 
    if (head == NULL) 
        return 0; 
  
    // count is 1 + count of remaining list 
    return 1 + getCount(head->next); 
} 

int getTextureAllocationInBytets()
{
    return getCount(textureCache) * sizeof(struct TextureCache);
}

void DestroryTextureCache()
{
    struct TextureCache *prev = textureCache;
    while (textureCache)
    {
        textureCache = textureCache->next;
        SDL_DestroyTexture(prev->texture);
 	      free(prev);
 	      prev = textureCache;
    }
}


#endif