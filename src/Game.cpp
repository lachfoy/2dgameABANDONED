#include "Game.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "Crosshair.h"
#include "ParticleManager.h"
#include "GameStateManager.h"

#define DEBUG_DRAW 0

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

    onCreate(); // call the game create functions -- mostly create all the managers and load resources

    //SDL_ShowCursor(SDL_DISABLE); // hide the cursor (doesn't work on WSL window)

    Uint32 start = 0;
    float dt = 0.0f;
    Uint32 dt_ms = 0;
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        // update the input manager which polls sdl events
        inputManager->update();
        if (inputManager->quitRequested() | inputManager->keyPressed(SDL_SCANCODE_ESCAPE)) quit = true;
        if (inputManager->keyDown(SDL_SCANCODE_P))
        {
            //gameState = (gameState == GAMESTATE_PAUSED) ? GAMESTATE_DEFAULT : GAMESTATE_PAUSED;
            m_gameStateManager->togglePaused();
            if (m_gameStateManager->getPaused()) printf("PAUSED GAME\n");
        }

        // calculate timestep
        dt = (SDL_GetTicks() - start) / 1000.0f;

        SDL_SetRenderDrawColor(renderer, 0xde, 0xde, 0xde, 0xff);
        SDL_RenderClear(renderer);
        if (!m_gameStateManager->getPaused())
        {
            gameUpdate(dt); // let the game update all the game logic
            gameRender(); // let the game copy everything to the renderer
        }
        else
        {
            gameRender();
            pausedRender();
        }
        SDL_RenderPresent(renderer);

        start = SDL_GetTicks();
        dt_ms = (Uint32)(dt * 1000);
        if (16 > dt_ms) SDL_Delay(16 - dt_ms); // 30fps framecap
    }

    onDestroy(); // cleanup resources
}

void Game::onCreate()
{
    ///////// game scene
    //bitmapFont = new BitmapFont(renderer, "../fonts/mig68000_8x16.bmp");
    inputManager = new InputManager();
    m_gameStateManager = new GameStateManager();
    resourceManager = new ResourceManager(renderer);
    resourceManager->loadTextures();

    uiManager = new UiManager(inputManager, resourceManager);
    particleManager = new ParticleManager(resourceManager);
    projectileManager = new ProjectileManager(resourceManager, particleManager);

    player = new Player(100.0f, 200.0f, resourceManager, uiManager, projectileManager);
    
    enemyManager = new EnemyManager(resourceManager, uiManager, projectileManager, player);
    enemyManager->addSkeleton(400.0f, 300.0f);
    enemyManager->addSkeleton(600.0f, 400.0f);
    enemyManager->addSkeleton(500.0f, 500.0f);
    enemyManager->addSkeleton(300.0f, 400.0f);
    enemyManager->addSkeleton(700.0f, 200.0f);

    //uiManager->addCrosshair(200, 200, 40, 40);
    //uiManager->addTextObject(200, 200, "Hello World");

    ///////// pause scene
    pauseUiManager = new UiManager(inputManager, resourceManager);
    pauseUiManager->addTextObject(windowWidth/2, windowHeight/2, "Paused!");
}

void Game::onDestroy()
{
    // game scene
    delete player;
    delete projectileManager;
    delete enemyManager;
    delete particleManager;
    delete uiManager;

    // pause scene
    delete pauseUiManager;

    delete resourceManager; // deallocate the resources
    delete m_gameStateManager;
    delete inputManager;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::gameUpdate(float dt)
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

void Game::pausedUpdate(float dt)
{

}

void Game::gameRender()
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

void Game::pausedRender()
{
    SDL_Rect screenFill = {0, 0, windowWidth, windowHeight};
    SDL_SetRenderDrawColor(renderer, 0x74, 0x74, 0x74, 0x74);
    SDL_RenderFillRect(renderer, &screenFill);
    pauseUiManager->renderUiObjects(renderer);
}