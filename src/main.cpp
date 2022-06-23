#include <stdio.h>
#include <SDL2/SDL.h>

#include "Player.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Player* player = new Player();

bool init();
void cleanUp();
void update(float dt);
void render();

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(window == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(window == NULL)
    {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void cleanUp()
{
    delete player;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void update(float dt)
{
    player->update(dt);
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0x90, 0x90, 0x90, 0xFF);
    SDL_RenderClear(renderer);
    
    player->render(renderer);
    
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    if(init())
    {
        Uint32 now = SDL_GetPerformanceCounter();
        Uint32 last = 0;
        float dt = 0;
        bool quit = false;
        SDL_Event e;
        while(!quit)
        {
            // poll events
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                player->handleInput(e);
            }

            last = now;
            now = SDL_GetPerformanceCounter();

            // update
            update(dt);

            // calculate dt
            dt = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

            // render
            render();
        }
    }

    cleanUp();

    return 0;
}