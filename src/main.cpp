#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect rect = { 100, 100, 64, 64 };
int playerVelX;
int playerVelY;
float playerMoveSpeed = 1;

bool init();
void cleanUp();
void handleInput(SDL_Event& e);
void update(float dt);

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void handleInput(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        SDL_Keycode keyCode = e.key.keysym.sym;
        if (keyCode == SDLK_UP)
        {
            playerVelX = 0;
            playerVelY = -1;
        }
        if (keyCode == SDLK_DOWN)
        {
            playerVelX = 0;
            playerVelY = 1;
        }
        if (keyCode == SDLK_LEFT)
        {
            playerVelX = -1;
            playerVelY = 0;
        }
        if (keyCode == SDLK_RIGHT)
        {
            playerVelX = 1;
            playerVelY = 0;
        }
    }
}

void update(float dt)
{
    
    rect.x += playerVelX * playerMoveSpeed;
    rect.y += playerVelY * playerMoveSpeed;

}

int main(int argc, char* argv[])
{
    if(init())
    {
        bool quit = false;
        SDL_Event e;
        while(!quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                handleInput(e);
            }

            update(0);

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x11, 0xaa, 0xff);
            SDL_RenderFillRect(renderer, &rect);

            SDL_RenderPresent(renderer);
        }
    }

    cleanUp();

    return 0;
}