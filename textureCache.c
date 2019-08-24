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
    TextureCache *current = textureCache;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(struct TextureCache));
    current->next->texture = newTexture;
    current->next->next = NULL;
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

void DestroryTextureCache()//TextureCache **cache)
{
    struct TextureCache *current = textureCache;
    struct TextureCache *next;

    int i = 0;
    while (current != NULL) {
        next = current->next;
        SDL_DestroyTexture(current->texture);
        free(current);
        current = next;
        i++;
    }
}


#endif