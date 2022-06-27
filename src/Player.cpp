#include "Player.h"

Player::Player()
{
    // initialize everything
    posX = 100.0f;
    posY = 100.0f;
    playerW = 40;
    playerH = 60;
    velX = 0;
    velY = 0;
    moveSpeed = 200.0f;
    collider = new AABB(posX, posY, 40, 64);
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

    // move the collider as well
    collider->upperBound.x = posX - (playerW / 2);
    collider->upperBound.y = posY - playerH;
    collider->lowerBound.x = posX + (playerW / 2);
    collider->lowerBound.y = posY;
}

void Player::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)posX - (playerW / 2);
    player_rect.y = (int)posY - playerH;
    player_rect.w = playerW;
    player_rect.h = playerH;
    SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff blue
    SDL_RenderFillRect(renderer, &player_rect);

    // draw a rect representing the collider
    // SDL_Color collider_color;
    // collider_color.a = 0xff;
    // collider_color.r = 0xff;
    // collider_color.g = 0xff;
    // collider_color.b = 0xff;
    // collider->debugRender(renderer, collider_color);

    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 6;
    debug_point_pos.h = 6;
    debug_point_pos.x = (int)posX - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)posY - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point_pos);
}