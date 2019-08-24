#ifndef __TEXT
#define __TEXT

#include "text.h"
#include "utils.h"
#include "textureCache.h"

void WriteText(SDL_Renderer *Renderer, TTF_Font *Font, const char *Text, SDL_Point pos, SDL_Color Color)
{
    SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_Surface *fontSurface = TTF_RenderText_Blended(Font, Text, Color); // create font surface
    SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(Renderer, fontSurface);  // create the texture

    SDL_Rect *fontRect = &fontSurface->clip_rect;
    fontRect->x = pos.x;
    fontRect->y = pos.y;
    SDL_RenderCopy(Renderer, fontTexture, NULL, fontRect); // copy text to the renderer

    SDL_RenderDrawPoint(Renderer, 0, 0);

    PushTextureCache(fontTexture);
    SDL_FreeSurface(fontSurface);
}

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void DrawRandomText(SDL_Renderer *Renderer, TTF_Font *Font, int dur)
{
    int randX = RandomNumber(0, SCREEN_WIDTH - 50);
    int randY = RandomNumber(0, SCREEN_HEIGHT - 50);

    SDL_Point pos = {randX, randY};

    char randText[100];
    rand_string(randText, 100);

    if(SDL_GetTicks() % 500)
    {
        WriteText(Renderer, Font, randText, pos, COLOR_WHITE);
    }
}

#endif