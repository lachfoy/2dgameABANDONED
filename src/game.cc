#include "game.h"

#include "InputManager.h"
#include "resource_manager.h"
#include "UiManager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "projectile_manager.h"
#include "player.h"
#include "debug_text_manager.h"
#include "enemy_manager.h"
#include "enemy_spawn_handler.h"

#define DEBUG_DRAW 0

Game::Game() {}

// init all the framework resources - SDL2, ttf etc.
bool Game::Init(int window_width, int window_height)
{
    window_width_ = window_width;
    window_height_ = window_height;

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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    // if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
    // {
    //   printf("Linear filtering not supported\n");
    // }  

    window_ = SDL_CreateWindow("sdl2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width_, window_height_, 0);
    if (window_ == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == NULL)
    {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

    return true;
}

void Game::Run()
{
    srand((unsigned)time(0)); // initialize prng

    Create();

    //SDL_ShowCursor(SDL_DISABLE); // hide the cursor (doesn't work on WSL window)

    Uint32 start = 0;
    float dt = 0.0f;
    Uint32 dt_ms = 0;
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        // update the input manager which polls sdl events
        input_manager_->update();
        if (input_manager_->quitRequested() | input_manager_->keyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // calculate timestep
        dt = (SDL_GetTicks() - start) / 1000.0f;

        Update(dt);

        SDL_RenderClear(renderer_);
        Render(renderer_);
        SDL_RenderPresent(renderer_);

        start = SDL_GetTicks();

        dt_ms = (Uint32)(dt * 1000);
        if (16 > dt_ms)
            SDL_Delay(16 - dt_ms); // 60fps framecap
    }

    Destroy(); // cleanup resources
}

void Game::Create()
{
    input_manager_ = std::make_shared<InputManager>();
    
    resource_manager_ = std::make_shared<ResourceManager>(renderer_);
    resource_manager_->LoadFonts();
    resource_manager_->LoadTextures();
    resource_manager_->LoadSounds();

    ui_manager_ = std::make_shared<UiManager>(input_manager_, resource_manager_, window_width_, window_height_);

    particle_manager_ = std::make_shared<ParticleManager>(resource_manager_);
    
    particle_emitter_manager_ = std::make_shared<ParticleEmitterManager>(particle_manager_);

    projectile_manager_ = std::make_shared<ProjectileManager>(resource_manager_, particle_manager_, particle_emitter_manager_);

    const Vec2f playerPos = { 100.0f, 200.0f };
    player_ = std::make_shared<Player>(playerPos, resource_manager_, particle_emitter_manager_, *ui_manager_, projectile_manager_);
    
    debug_text_manager_ = std::make_shared<DebugTextManager>(resource_manager_->GetFont("debug_font"));

    enemy_manager_ = std::make_shared<EnemyManager>(resource_manager_, particle_emitter_manager_, ui_manager_, projectile_manager_, player_);
    
    enemy_spawn_handler_ = std::make_shared<EnemySpawnHandler>(enemy_manager_, window_width_, window_height_);
}

void Game::Update(float dt)
{
    // handle input
    player_->handleInput(*input_manager_);

    // game logic
    enemy_spawn_handler_->Update(dt);
    enemy_manager_->ResolvePlayerProjectileCollisions(projectile_manager_->player_projectiles());
    player_->resolveEnemyCollisions(enemy_manager_->enemies());

    // update game objects
    player_->Update(dt);
    enemy_manager_->UpdateEnemies(dt);
    projectile_manager_->UpdateProjectiles(dt);
    particle_manager_->UpdateParticles(dt);
    particle_emitter_manager_->UpdateParticleEmitters(dt);

    // update ui objects
    //ui_manager_->updateUiObjects(dt);
    debug_text_manager_->Update(*player_);


    // clean up all unused objects AT THE END of the update
    enemy_manager_->CleanUpUnusedEnemies();
    projectile_manager_->CleanUpUnusedProjectiles();

    //ui_manager_->removeUnusedUiObjects();
}

void Game::Render(SDL_Renderer* renderer)
{
    // render background hehhe
    const SDL_Rect background_rect = { 0, 0, window_width_, window_height_ };
    SDL_RenderCopy(renderer, resource_manager_->GetTexture("background_forest_texture"), NULL, &background_rect);

    // render game objects
    enemy_manager_->RenderEnemies(renderer);
    player_->Render(renderer);
    particle_manager_->RenderParticles(renderer);
    projectile_manager_->RenderProjectiles(renderer);

    // render ui objects
    //ui_manager_->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        enemy_manager_->RenderDebug(renderer);
        player_->RenderDebug(renderer);
        projectile_manager_->renderDebug(renderer);
        debug_text_manager_->Render(renderer);
    }

}

void Game::Destroy()
{
    resource_manager_->CleanUpResources();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}