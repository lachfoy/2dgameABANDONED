#include "Player.h"

Player::Player()
{
    // initialize everything
    posX = 100.0f;
    posY = 100.0f;
    rect.x = (int)posX;
    rect.y = (int)posY;
    rect.w = 40;
    rect.h = 64;
    velX = 0;
    velY = 0;
    moveSpeed = 200.0f;

    debug_point.x = 0;
    debug_point.y = 0;
    debug_point.w = 6;
    debug_point.h = 6;
}

void Player::handleInput(SDL_Event& e) // use keystate instead?
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;
        if (keyCode == SDLK_UP)
            velY = -1;
        if (keyCode == SDLK_DOWN)
            velY = 1;
        if (keyCode == SDLK_LEFT)
            velX = -1;
        if (keyCode == SDLK_RIGHT)
            velX = 1;
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        const SDL_Keycode keyCode = e.key.keysym.sym;
        if (e.key.keysym.sym == SDLK_UP)
            velY = 0;
        if (e.key.keysym.sym == SDLK_DOWN)
            velY = 0;
        if (e.key.keysym.sym == SDLK_LEFT)
            velX = 0;
        if (e.key.keysym.sym == SDLK_RIGHT)
            velX = 0;
    }
}

void Player::update(float dt)
{
    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;

    // also reposition the visual representation of the player
    rect.x = (int)posX - (rect.w / 2);
    rect.y = (int)posY - (rect.h);

    debug_point.x = (int)posX - (debug_point.w / 2);
    debug_point.y = (int)posY - (debug_point.h/ 2);
}

void Player::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff blue
    SDL_RenderFillRect(renderer, &rect);

    // draw the origin position representing the actual x and y positions
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point);
}