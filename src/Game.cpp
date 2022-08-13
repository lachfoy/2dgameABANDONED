#include "Game.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "Crosshair.h"
#include "ParticleManager.h"
#include "SceneManager.h"

Game::Game() {}

// init all the framework resources - SDL2, ttf etc.
bool Game::init(int w, int h)
{
    // initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // initialize sdl_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Unable to initialize SDL_image: %s\n", IMG_GetError());
        return false;
    }

    // initialize sdl_ttf
    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    // initialize SDL_mixer
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
    {
      printf("Linear filtering not supported\n");
    }  

    windowWidth = w;
    windowHeight = h;

    window = SDL_CreateWindow("sdl2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
    if (window == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return true;
}

void Game::run()
{
    srand((unsigned)time(0)); // initialize prng

    create(); // call the game create functions -- mostly create all the managers and load resources

    //SDL_ShowCursor(SDL_DISABLE); // hide the cursor (doesn't work on WSL window)

    Uint32 start = 0;
    float dt = 0.0f;
    Uint32 dt_ms = 0;
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        // update the input manager which polls sdl events
        m_inputManager->update();
        if (m_inputManager->quitRequested() | m_inputManager->keyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
        if (m_inputManager->keyDown(SDL_SCANCODE_P))
        {
            //gameState = (gameState == PAUSED) ? GAME : PAUSED;
            m_sceneManager->togglePaused();
            if (m_sceneManager->getPaused()) printf("PAUSED GAME\n");
        }

        // calculate timestep
        dt = (SDL_GetTicks() - start) / 1000.0f;

        SDL_SetRenderDrawColor(renderer, 0xde, 0xde, 0xde, 0xff);
        SDL_RenderClear(renderer);
            if (m_sceneManager->inMenu())
            {
                //menuUpdate(dt);
                //menuRender();
            }
            else
            {
                if (!m_sceneManager->getPaused())
                {
                    //gameUpdate(dt); // let the game update all the game logic
                    //gameRender(); // let the game copy everything to the renderer
                }
                else
                {
                    //gameRender();
                    //pauseRender();
                }
            }
        SDL_RenderPresent(renderer);

        start = SDL_GetTicks();

        dt_ms = (Uint32)(dt * 1000);
        if (16 > dt_ms)
            SDL_Delay(16 - dt_ms); // 60fps framecap
    }

    destroy(); // cleanup resources
}

void Game::create()
{
    
    m_inputManager = new InputManager();
    m_resourceManager = new ResourceManager(renderer);

    m_sceneManager = new SceneManager();
    m_sceneManager->setScene(SceneManager::MENU); // default to menu

    


    /////// menu scene
    //menuUiManager = new UiManager(inputManager, resourceManager, windowWidth, windowHeight);
    //menuUiManager->addTextObject(windowWidth / 2 - 60, windowHeight / 2 - 200, "Game Menu");
}

void Game::destroy()
{
    delete m_resourceManager; // deallocate the resources
    delete m_sceneManager;
    delete m_inputManager;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}