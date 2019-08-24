#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdio.h>
#include <SDL.h>

#include "types.h"

#define MAX_KEYS 287

global_variable int STEP = 5;

void InitKeyboardState(void);
void HandleMovement(SDL_Rect *pos);

#endif