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
    player->handleInput(e);
}

void Game::onUpdate(float dt)
{
    player->update(dt);
}

void Game::onRender()
{
    SDL_SetRenderDrawColor(renderer, 0x90, 0x90, 0x90, 0xFF);
    SDL_RenderClear(renderer);
    
    player->render(renderer);

    SDL_Color collider_color;
    collider_color.a = 0xff;
    collider_color.r = 0xff;
    collider_color.g=0x00;
    collider_color.b=0x00;
    if (AABB::testOverlap(*player->collider, *test_collider))
        collider_color.g = 0xff;
    else
        collider_color.g=0x00;
    test_collider->debugRender(renderer, collider_color);
    
    SDL_RenderPresent(renderer);
}