#ifndef __TEXT_H
#define __TEXT_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#include <SDL.h>
#include <SDL_ttf.h>

#if defined(__WIN32) || defined(__WIN64)
#define FONT_BASEDIR "C:\\Windows\\Fonts\\"
#elif defined(__linux__)
#define FONT_BASEDIR "/usr/shar/fonts/"
#else
#define FONT_BASEDIR "OS UNDEFINED"
#endif

#define TTF_FONT_PATH(a) concat(2, FONT_BASEDIR, a)


char* concat(int howMany, ...)
{
    va_list strP;

    va_start(strP, howMany);
    int size = 1;
    for (int i = 0; i < howMany; i++)
        size += strlen(va_arg(strP, char*));
    va_end(strP);

    char *result = malloc(size);

    va_start(strP, howMany);
    strcpy(result, va_arg(strP, char*));
    for (int i = 1; i < howMany; i++)
        strcat(result, va_arg(strP, char*));
    va_end(strP);

    return result;
}

TTF_Font* LoadFont(char *filename, int ptsize)
{
    char *path = TTF_FONT_PATH(filename);
    TTF_Font *font = TTF_OpenFont(path, ptsize);
    SDL_Log("Loaded Font %s", path);
    free(path);
    if(font == NULL)
        return NULL;
    
    return font;
}

void WriteText(SDL_Renderer *Renderer, TTF_Font *font, const char *text, SDL_Point pos, SDL_Color color);

#endif