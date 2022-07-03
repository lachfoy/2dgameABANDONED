#include "Game.h"

#include "AABB.h"
#include "Player.h"
#include "Skeleton.h"
#include "HealthBar.h"
#include "ProjectileManager.h"
#include "Fireball.h"

Game::Game(){}

void Game::onCreate()
{
    player = new Player(100.0f, 200.0f);
    projectileManager = new ProjectileManager();
    playerHealthBar = new HealthBar(20, 20);
    test_collider = new AABB(300.0f, 200.0f, 200.0f, 100.0f);
    enemies.push_back(new Skeleton(400.0f, 300.0f));
}

void Game::onCleanup()
{
    delete player;
    delete test_collider;
    delete projectileManager;
    //projectiles.clear();
    enemies.clear();
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
    /* NO COLLISIONS ATM ------- HANDLE THIS IN A DIFFERENT WAY 
    // test projectile collisions
    for (int i = 0; i < projectiles.size(); i++)
    {
        if (AABB::testOverlap(*projectiles[i]->collider, *test_collider)) {}
        
        // test projectiles against enemies
        for (int j = 0; j < enemies.size(); j++)
        {
            if (AABB::testOverlap(*projectiles[i]->collider, *enemies[j]->collider))
            {
                enemies[j]->doDamage(projectiles[i]->damage);
                projectiles[i]->removeable = true; // flag that projectile as safe to remove
            }
        }
    }
    */

    for (int i = 0; i < enemies.size(); i++)
    {
        projectileManager->resolveEnemyCollisions(enemies[i]);
    }

    // update the player
    player->update(dt);

    // update all the projectiles
    projectileManager->updateProjectiles(dt);

    // update all the enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->update(dt);
        if (enemies[i]->removeable)
        {
            delete enemies[i];
            enemies.erase(enemies.begin() + i); // delete if remove flag is set
        }
    }
}

void Game::onRender()
{
    player->render(renderer);

    // render the projectiles
    projectileManager->renderProjectiles(renderer);

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(renderer);
    }

    // render UI objects
    playerHealthBar->render(renderer);
}