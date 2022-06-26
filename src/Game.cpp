#include "Game.h"

Game::Game(){}

void Game::onCreate()
{
    player = new Player();
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
    
    SDL_RenderPresent(renderer);
}