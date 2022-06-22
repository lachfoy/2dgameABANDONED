#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect rect = { 0, 0, 64, 64 };
float posX;
float posY;
int velX;
int velY;
float moveSpeed = 200.0f;

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

void handleInput(SDL_Event& e) // take a const Uint8* keystates instead?
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_UP)
        {
            printf("Up key pressed\n");
            velX = 0;
            velY = -1;
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            printf("Down key pressed\n");
            velX = 0;
            velY = 1;
        }
        if (e.key.keysym.sym == SDLK_LEFT)
        {
            printf("Left key pressed\n");
            velX = -1;
            velY = 0;
        }
        if (e.key.keysym.sym == SDLK_RIGHT)
        {
            printf("Right key pressed\n");
            velX = 1;
            velY = 0;
        }
    }


}

void update(float dt)
{
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;
    rect.x = (int)posX;
    rect.y = (int)posY;
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

                handleInput(e);
            }

            last = now;
            now = SDL_GetPerformanceCounter();

            // update
            update(dt);

            // calculate dt
            dt = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

            // render
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff
            SDL_RenderFillRect(renderer, &rect);

            SDL_RenderPresent(renderer);
        }
    }

    cleanUp();

    return 0;
}