#include "Game.h"

Game::Game(){}

void Game::onCreate()
{
    player = new Player();
    test_collider = new AABB(300, 200, 200, 100);
}

void Game::onCleanup()
{
    delete player;
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

            case SDLK_SPACE:
                projectiles.push_back(new Projectile(player->pos.x, player->pos.y - 30, 1, 0));
                break;
        }
    }
}

void Game::onUpdate(float dt)
{
    player->update(dt);
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->update(dt);
    }
}

void Game::onRender()
{
    SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff);
    SDL_RenderClear(renderer);
    
    player->render(renderer);

    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->render(renderer);
    }

    SDL_Color test_collider_color = { 0xff, 0x00, 0x00, 0xff };
    if (AABB::testOverlap(*player->collider, *test_collider))
        test_collider_color.g = 0xff;

    for (int i = 0; i < projectiles.size(); i++)
    {
        if (AABB::testOverlap(*projectiles[i]->collider, *test_collider))
        test_collider_color.g = 0xff;
    }

    test_collider->debugRender(renderer, test_collider_color);
    
    SDL_RenderPresent(renderer);
}