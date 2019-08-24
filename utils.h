#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "types.h"

void ExitProgram(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);

void clamp(int *val, int min, int max);

void InitalizeSeed();
void seedRandomNumber();
int RandomNumber(int min, int max);
SDL_Color RandomColor();
void PadRect(SDL_Rect *Rect, int padding);

void DrawRect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color fill);
void DrawRectWithBorder(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color fill, SDL_Color border);
void DrawRectWithThickBorder(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color fill, int borderSize, SDL_Color border);

#endif