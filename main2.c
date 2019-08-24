#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

// path to fonts location
#define TTF_FONT_PATH(file) "C:\\Windows\\Fonts\\"file

int main( int argc, char *argv[] )
{
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
        compiled.major, compiled.minor, compiled.patch);
    printf("But we are linking against SDL version %d.%d.%d.\n",
        linked.major, linked.minor, linked.patch);

    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    
    // setup window and renderer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    if(TTF_Init() < 0)
    {
        SDL_Log("Unable to initialize SDL TTF: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window < 0)
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(renderer < 0)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    TTF_Font *font = TTF_OpenFont(TTF_FONT_PATH("arial.ttf"), 15);

    Uint8 isRunning = 1;

    SDL_Point mouse;
    SDL_Rect *rect1 = &(SDL_Rect){500, 200, 50, 50};
    SDL_Rect *rect2 = &(SDL_Rect){30, 30, 100, 100};

    char someString[255];

    SDL_Event event;
    while(isRunning == 1)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);

        // handle events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = 0;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mouse.x, &mouse.y);
            }
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // draw a white rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, rect1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, rect2);

        // define string with mouse x, y coords
        sprintf(someString, "x: %d, y: %d", mouse.x, mouse.y);
        SDL_Point textPos = {10, 10};
        SDL_Surface *fontSurface = TTF_RenderText_Blended(font, someString, (SDL_Color){0, 0, 0, 255}); // create font surface
        SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);  // create the texture

        // get clip widh and height from fontsurface clip rect
        SDL_Rect fontRect = fontSurface->clip_rect;
        fontRect.x = textPos.x; 
        fontRect.y = textPos.y;

        // copy text to renderer
        SDL_RenderCopy(renderer, fontTexture, NULL, &fontRect);

        // remove this and screen goes blank
        SDL_RenderDrawPoint(renderer, 0, 0);

        // delete surface and texture
        SDL_FreeSurface(fontSurface);
        SDL_DestroyTexture(fontTexture);

        // finish rendering
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}