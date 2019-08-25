#ifndef __TYPE_H
#define __TYPE_H

#include <stdio.h>
#include <SDL.h>

#define global_variable static
global_variable int SCREEN_WIDTH = 800;
global_variable int SCREEN_HEIGHT = 600;

typedef struct oscVal {
    int value;
    int min;
    int max;
    int step;
    int tickDur;
    int lastTickCount;
} oscVal;

typedef int bool;
#define true 1
#define false 0

#define COLOR_WHITE (SDL_Color){255, 255, 255, 255}
#define COLOR_BLACK (SDL_Color){0, 0, 0, 255}
#define COLOR_PINK (SDL_Color){240, 50, 170, 255}
#define COLOR_RED (SDL_Color){255, 0, 0, 255}
#define COLOR_TRANSPARENT (SDL_Color){255, 255, 255, 25}

#endif