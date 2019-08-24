#ifndef __UTILS
#define __UTILS

#include <stdlib.h>
#include <time.h>

#include "utils.h"

void clamp(int *value, int min, int max)
{
    if(*value < min) *value = min;
    else if(*value > max) *value = max;
}

void InitalizeSeed()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }
}

int RandomNumber(int min, int max)
{
    return rand() % max + min;
}

SDL_Color RandomColor()
{
    SDL_Color Result;
    Result.r = RandomNumber(0, 255);
    Result.g = RandomNumber(0, 255);
    Result.b = RandomNumber(0, 255);
    Result.a = 255;//RanomNumber(0, 255);

    return Result;
}

void PadRect(SDL_Rect *Rect, int padding)
{
    Rect->x -= padding;
    Rect->y -= padding;
    Rect->w += (padding * 2);
    Rect->h += (padding * 2);
}

void oscillateValueBetween(oscVal *obj, int min, int max, int tickInterval)
{
    if (SDL_GetTicks() - obj->lastTickCount > tickInterval)
    {
        obj->lastTickCount = SDL_GetTicks();
        obj->value += obj->step;
        if ((obj->value <= min) || (obj->value >= max)) {
            obj->step *= -1;
        }
    }
    clamp(&obj->value, min, max);
}

// draw rectangle outline
void DrawRect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color border)
{
    SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
    SDL_RenderDrawRect(renderer, rect);
}

void DrawFillRect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color fill)
{
    SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, fill.a);
    SDL_RenderFillRect(renderer, rect);
}

void DrawFillRectBorder(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color fill, int borderSize, SDL_Color border)
{
    if(borderSize < 1 || borderSize > rect->w || borderSize > rect->h)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "Invalid border size!");
        return;
    }

    if(borderSize == 1)
    {
        DrawFillRect(renderer, rect, fill);
        DrawRect(renderer, rect, border);
    }
    else
    {
        // fill base rect as border
        DrawFillRect(renderer, rect, border);

        // now draw forground rect and fill with color
        int halfBorder = borderSize / 2; // get half border thinkness
        rect->x += halfBorder;           // move x pos by half border
        rect->y += halfBorder;           // move y pos by half border  
        rect->w -= borderSize;           // reduce width by size of border
        rect->h -= borderSize;           // reduct height by size of border
        DrawFillRect(renderer, rect, fill);
    }
}

#endif