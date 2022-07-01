#include "Game.h"

Game::Game(){}

void Game::onCreate()
{
    player = new Player();
    playerHealthBar = new HealthBar(20, 20);
    test_collider = new AABB(300, 200, 200, 100);
    enemies.push_back(new Enemy(400, 400));
}

void Game::onCleanup()
{
    delete player;
    delete test_collider;
    projectiles.clear();
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
                projectiles.push_back(new Fireball(player->pos.x, player->pos.y - 30, 1, 0));
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
    if (AABB::testOverlap(*player->collider, *test_collider)) {}

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

    // update the player
    player->update(dt);

    // update all the projectiles
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->update(dt);
        if (projectiles[i]->removeable) projectiles.erase(projectiles.begin() + i); // delete if remove flag is set
    }

    // update all the enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->update(dt);
        if (enemies[i]->removeable) enemies.erase(enemies.begin() + i); // delete if remove flag is set
    }
}

void Game::onRender()
{
    player->render(renderer);

    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->render(renderer);
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(renderer);
    }

    test_collider->debugRender(renderer);

    // render UI objects
    playerHealthBar->render(renderer);
}