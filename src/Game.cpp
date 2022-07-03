#include "Game.h"

#include "AABB.h"
#include "Player.h"
#include "Skeleton.h"
#include "HealthBar.h"
#include "ProjectileManager.h"
#include "Fireball.h"
#include "EnemyManager.h"

Game::Game(){}

void Game::onCreate()
{
    player = new Player(100.0f, 200.0f);
    projectileManager = new ProjectileManager();
    enemyManager = new EnemyManager();
    playerHealthBar = new HealthBar(20, 20);
    test_collider = new AABB(300.0f, 200.0f, 200.0f, 100.0f);
    enemyManager->addEnemy(new Skeleton(400.0f, 300.0f));
}

void Game::onCleanup()
{
    delete player;
    delete test_collider;
    delete projectileManager;
    //projectiles.clear();
    delete enemyManager;
}

void Game::handleInput(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                player->velY = -1;
                break;

            case SDLK_DOWN:
            case SDLK_s:
                player->velY = 1;
                break;

            case SDLK_LEFT:
            case SDLK_a:
                player->velX = -1;
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                player->velX = 1;
                break;
            
            case SDLK_SPACE:
                //projectiles.push_back(new Fireball(player->pos.x, player->pos.y - 30, 1, 0));
                projectileManager->addProjectile(new Fireball(projectileManager, player->pos.x, player->pos.y - 30, 1, 0));
                break;

            case SDLK_k: // deal damage to player
                player->doDamage(11);
                playerHealthBar->updateHealth(player);
                break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                player->velY = 0;
                break;

            case SDLK_DOWN:
            case SDLK_s:
                player->velY = 0;
                break;

            case SDLK_LEFT:
            case SDLK_a:
                player->velX = 0;
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                player->velX = 0;
                break;
        }
    }
}

void Game::onUpdate(float dt)
{
    // resolve projectile vs enemy collisions
    enemyManager->resolveProjectileCollisions(projectileManager->getProjectiles());

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
    player->render(renderer);
    enemyManager->renderEnemies(renderer);
    projectileManager->renderProjectiles(renderer);

    // render UI objects
    playerHealthBar->render(renderer);
}