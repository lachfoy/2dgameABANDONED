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
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                velY = -1;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                velY = 1;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                velX = -1;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                velX = 1;
                break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                velY = 0;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                velY = 0;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                velX = 0;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                velX = 0;
                break;
        }
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