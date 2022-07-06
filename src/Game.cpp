#include "Game.h"

#include "AABB.h"
#include "Player.h"
#include "HealthBar.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UIManager.h"

Game::Game(){}

void Game::onCreate()
{
    _UIManager = new UIManager();
    player = new Player(*_UIManager, 100.0f, 200.0f);
    projectileManager = new ProjectileManager();
    enemyManager = new EnemyManager();
    test_collider = new AABB(300.0f, 200.0f, 200.0f, 100.0f);
    enemyManager->addSkeleton(player, *_UIManager, 400.0f, 300.0f);
}

void Game::onCleanup()
{
    delete player;
    delete projectileManager;
    delete enemyManager;
    delete _UIManager;
}

void Game::handleInput(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;

        if (keyCode == SDLK_UP || keyCode == SDLK_w)
            player->velY = -1;

        if (keyCode == SDLK_DOWN || keyCode == SDLK_s)
            player->velY = 1;

        if (keyCode == SDLK_LEFT || keyCode == SDLK_a)
            player->velX = -1;

        if (keyCode == SDLK_RIGHT || keyCode == SDLK_d)
            player->velX = 1;
            
        else if (keyCode == SDLK_SPACE || keyCode == SDLK_z)
        {
            if (player->facingDir == Player::FACING_RIGHT) projectileManager->addFireball(player->pos.x, player->pos.y - 30, 1, 0);
            else projectileManager->addFireball(player->pos.x, player->pos.y - 30, -1, 0);
        }

        else if (keyCode == SDLK_k)
        {
            player->doDamage(11);
            projectileManager->addFireballExplosion(player->pos.x, player->pos.y);
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;
        
        if (keyCode == SDLK_UP || keyCode == SDLK_w)
            player->velY = 0;

        if (keyCode == SDLK_DOWN || keyCode == SDLK_s)
            player->velY = 0;

        if (keyCode == SDLK_LEFT || keyCode == SDLK_a)
            player->velX = 0;

        if (keyCode == SDLK_RIGHT || keyCode == SDLK_d)
            player->velX = 0;
    }
}

void Game::onUpdate(float dt)
{
    // resolve projectile vs enemy collisions
    enemyManager->resolveProjectileCollisions(projectileManager->getProjectiles());

    // resolve enemy vs player collisions
    player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update the player
    player->update(dt);

    // update enemies
    enemyManager->updateEnemies(dt);

    // update projectiles
    projectileManager->updateProjectiles(dt);
}

void Game::onRender()
{
    // render game objects
    enemyManager->renderEnemies(renderer);
    player->render(renderer);
    projectileManager->renderProjectiles(renderer);

    // render UI objects
    _UIManager->renderUIObjects(renderer);
}