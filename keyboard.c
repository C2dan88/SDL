#ifndef __KEYBOARD
#define __KEYBOARD

#include "keyboard.h"
#include "utils.c"

global_variable bool KEYS[MAX_KEYS];

void InitKeyboardState()
{
    for(int i = 0; i < MAX_KEYS; i++)
        KEYS[i] = false;
}

void HandleMovement(SDL_Rect *player)
{
    if(KEYS[SDL_SCANCODE_LEFT])
        player->x -= STEP;

    if(KEYS[SDL_SCANCODE_RIGHT])
        player->x += STEP;

    if(KEYS[SDL_SCANCODE_UP])
        player->y -= STEP;

    if(KEYS[SDL_SCANCODE_DOWN])
        player->y += STEP;
}

#endif