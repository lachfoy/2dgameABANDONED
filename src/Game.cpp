#include "Game.h"

#include "BitmapFont.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "Crosshair.h"
#include "ParticleManager.h"

#define DEBUG_DRAW 0

Game::Game() {}

bool Game::init(int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
    {
      printf("Linear filtering not supported\n");
    }  

    windowWidth = w;
    windowHeight = h;

    window = SDL_CreateWindow("sdl2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
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

void Game::run()
{
    srand((unsigned)time(0)); // initialize prng

    onCreate(); // call the game create functions

    SDL_ShowCursor(SDL_DISABLE); // hide the cursor (doesn't work on WSL window)

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

        SDL_SetRenderDrawColor(renderer, 0xde, 0xde, 0xde, 0xff);
        SDL_RenderClear(renderer);

        onRender(); // let the game copy everything to the renderer

        bitmapFont->renderText(renderer, 10, 10, "ms: " + std::to_string(dt_ms)); // render frametime (ms)

        SDL_RenderPresent(renderer);

        start = SDL_GetTicks();
        dt_ms = (Uint32)(dt * 1000);
        if (16 > dt_ms) SDL_Delay(16 - dt_ms); // 30fps framecap
    }

    onDestroy(); // cleanup resources
}

void Game::onCreate()
{
    uiManager = new UiManager(inputManager ,resourceManager);
    particleManager = new ParticleManager(resourceManager);
    projectileManager = new ProjectileManager(resourceManager, particleManager);

    player = new Player(100.0f, 200.0f, resourceManager, uiManager, projectileManager);
    
    enemyManager = new EnemyManager(resourceManager, uiManager, projectileManager, player);
    enemyManager->addSkeleton(400.0f, 300.0f);
    enemyManager->addSkeleton(600.0f, 400.0f);
    enemyManager->addSkeleton(500.0f, 500.0f);
    enemyManager->addSkeleton(300.0f, 400.0f);
    enemyManager->addSkeleton(700.0f, 200.0f);

    uiManager->addCrosshair(200, 200, 40, 40);
}

void Game::onDestroy()
{
    delete player;
    delete projectileManager;
    delete enemyManager;
    delete particleManager;
    delete uiManager;

    delete bitmapFont;
    delete inputManager;
    delete resourceManager; // deallocate the resources
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::onUpdate(float dt)
{
    // handle input
    player->handleInput(*inputManager);

    // update game objects
    player->updatePlayer(dt);
    enemyManager->updateEnemies(dt);
    projectileManager->updateProjectiles(dt);
    particleManager->updateParticles(dt);

    // collision resolution
    enemyManager->resolvePlayerProjectileCollisions(projectileManager->getPlayerProjectiles());
    player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update ui objects
    uiManager->updateUiObjects(dt);

    // remove unused objects
    enemyManager->removeUnusedEnemies();
    projectileManager->removeUnusedProjectiles();
    uiManager->removeUnusedUiObjects();
    particleManager->removeUnusedParticles();
}

void Game::onRender()
{
    // render game objects
    enemyManager->renderEnemies(renderer);
    player->renderShadow(renderer);
    player->render(renderer);
    particleManager->renderParticles(renderer);
    projectileManager->renderProjectiles(renderer);

    // render ui objects
    uiManager->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        enemyManager->renderDebug(renderer);
        player->renderDebug(renderer);
        projectileManager->renderDebug(renderer);
    }
}