#include "Engine.h"

#include "BitmapFont.h"
#include "InputManager.h"
#include "ResourceManager.h"

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

    inputManager = new InputManager();

    resourceManager = new ResourceManager(renderer);
    resourceManager->loadTextures();

    return true;
}

void Engine::cleanup()
{
    onCleanup(); // run the games cleanup functions

    delete bitmapFont;
    delete inputManager;
    delete resourceManager; // deallocate the resources
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Engine::run()
{
    srand((unsigned) time(0)); // initialize prng

    onCreate(); // call the game create functions

    Uint32 start = 0;
    float dt = 0.0f;
    Uint32 dt_ms = 0;
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        // update the input manager which polls sdl events
        inputManager->update();
        if (inputManager->quitRequested() | inputManager->keyDown(SDL_SCANCODE_ESCAPE)) quit = true;

        // calculate timestep
        dt = (SDL_GetTicks() - start) / 1000.0f;
        
        onUpdate(dt); // let the game update all the game logic

        SDL_SetRenderDrawColor(renderer, 0xd3, 0xd3, 0xd3, 0xff); // lightish grey
        SDL_RenderClear(renderer);

        onRender(); // let the game copy everything to the renderer

        bitmapFont->renderText(renderer, 10, 10, "ms: " + std::to_string(dt_ms)); // render frametime (ms)

        SDL_RenderPresent(renderer);

        start = SDL_GetTicks();
        dt_ms = (Uint32)(dt * 1000);
        if (16 > dt_ms) SDL_Delay(16 - dt_ms); // 30fps framecap
    }

    cleanup(); // cleanup resources
}