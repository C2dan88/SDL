#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "textureCache.c"
#include "utils.c"
#include "text.c"
#include "keyboard.c"
#include "framerate.c"

int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // setup window and renderer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //char input[10];
    // int result = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL, &window, &renderer);
    // if(result < 0)
    // {
    //     printf("Error unable to create Window and Renderer!\nSDL Error: %s\n", SDL_GetError());
    //     scanf("%10s", input);
    //     return 0;
    // }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (window < 0)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer < 0)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Delay(2000);

        return 0;
    }

    if (TTF_Init() < 0)
    {
        SDL_Log("Unable to initialize SDL TTF: %s", SDL_GetError());
        return 1;
    }

    TTF_Font *font = LoadFont("arial.ttf", 15);
    if (font == NULL)
    {
        printf("Unable to load font! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    bool isRunning = true;
    SDL_Event event;

    InitalizeSeed();
    InitKeyboardState();
    InitTextureCache();

    int startX = RandomNumber(50, SCREEN_WIDTH - 50);
    int startY = RandomNumber(50, SCREEN_WIDTH - 50);

    SDL_Rect player = {startX, startY, 50, 50};
    SDL_Color playerColor = RandomColor();
    SDL_Point mouse = {0, 0};

    char text[255];

    oscVal alphaObj = (oscVal){
        .value = 255,
        .step = -1,
        .lastTickCount = 0};

    oscVal textYPos = (oscVal){
        .value = 255,
        .step = -5,
        .lastTickCount = 0};

    fpsinit();
    char randText[100];
    rand_string(randText, 100);
    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        // clear screen
        SDL_SetRenderDrawColor(renderer, 240, 50, 170, 255);
        SDL_RenderClear(renderer);

        // handle events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                KEYS[event.key.keysym.scancode] = true;
                break;

            case SDL_KEYUP:
                KEYS[event.key.keysym.scancode] = false;
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse.x, &mouse.y);
                break;

            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    //SDL_Log("Old Window size %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
                    //SDL_Log("New Window size: %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                }
                break;
            }
        }

        HandleMovement(&player);
        clamp(&player.x, 0, SCREEN_WIDTH - player.w);
        clamp(&player.y, 0, SCREEN_HEIGHT - player.h);

        if (KEYS[SDL_SCANCODE_R])
            playerColor = RandomColor();

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_Rect borderRect = {100, 100, 200, 200};
        SDL_Color fillColor = COLOR_RED;
        //SDL_Log("%d\n", SDL_GetTicks() - alpha_ticks);
        // if (SDL_GetTicks() - alpha_ticks > 5) {
        //     alpha_ticks = SDL_GetTicks();
        //     alpha += alpha_step;
        //     if (alpha > 255) {
        //         alpha_step = -1;
        //     }
        //     if (alpha < 100) {
        //         alpha_step = 1;
        //     }
        //     clamp(&alpha, 100, 255);
        //     //SDL_Log("%d\n", alpha);
        // }

        //oscillateValueBetween(&alpha, 100, 255, -5, 100);
        oscillateValueBetween(&alphaObj, 100, 255, 2);
        fillColor.a = alphaObj.value;
        DrawFillRectBorder(renderer, &borderRect, fillColor, 25, COLOR_BLACK);

        // drawPlayer
        DrawFillRectBorder(renderer, &player, playerColor, 1, COLOR_BLACK);

        sprintf(text, "x: %d, y: %d", player.x, player.y);
        SDL_Point textPos = {10, 10};
        WriteText(renderer, font, text, textPos, COLOR_WHITE);

        fpsthink();
        sprintf(text, "FPS: %.0f", framespersecond);
        SDL_Point text2Pos = {SCREEN_WIDTH - 100, 10};
        WriteText(renderer, font, text, text2Pos, COLOR_WHITE);

        oscillateValueBetween(&textYPos, 100, 500, 20);
        SDL_Point text3pos = {10, textYPos.value};
        WriteText(renderer, font, randText, text3pos, COLOR_BLACK);

        //for(int i = 0; i < 500; i++)
        //    DrawRandomText(renderer, font, 500);

        // render the screen
        SDL_RenderPresent(renderer);
        DestroryTextureCache();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
            //SDL_Log("Delay : %d\n", frameDelay - frameTime);
        }
    }

    SDL_Log("Clean up\n");
    SDL_Log("%dbytes", getTextureAllocationInBytets());

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
