#ifndef __TEXT_H
#define __TEXT_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

void WriteText(SDL_Renderer *Renderer, TTF_Font *font, const char *text, SDL_Point pos, SDL_Color color);

#endif