#include "Engine.h"

Engine::Engine(){}

bool Engine::init(int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    width = w;
    height = h;

    window = SDL_CreateWindow("sdl2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
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

    bitmapFont = new BitmapFont(renderer, "../fonts/mig68000_8x16.bmp");
    if (!bitmapFont)
    {
        printf("Bitmap font could not be created: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Engine::cleanup()
{
    onCleanup(); // run the games cleanup functions

    delete bitmapFont;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Engine::run()
{
    onCreate(); // call the game create functions

    float elapsedMS = 0.0f; // testing my timer

    Uint32 timeNow = SDL_GetPerformanceCounter();
    Uint32 timeLast = 0;
    float dt = 0.0f;

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        dt = ((timeNow - timeLast) * 1000 / (float)SDL_GetPerformanceFrequency()) * 0.001f;
        elapsedMS += dt;

        // poll events
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }

            handleInput(e);
        }

        onUpdate(dt); // let the game update all the game logic

        SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff);
        SDL_RenderClear(renderer);

        onRender(); // let the game copy everything to the renderer

        bitmapFont->renderText(renderer, 10, 10, "fps: " + std::to_string(1.0f / dt)); // render FPS

        SDL_RenderPresent(renderer);
    }

    cleanup(); // cleanup resources
}