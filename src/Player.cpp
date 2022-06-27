#include "Player.h"

Player::Player()
{
    // initialize everything
    pos.x = 100.0f;
    pos.y = 100.0f;
    playerW = 40;
    playerH = 60;
    velX = 0;
    velY = 0;
    moveSpeed = 200.0f;
    collider = new AABB(pos.x, pos.y, 40, 64);
}

void Player::update(float dt)
{
    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    // move the collider as well
    collider->upperBound.x = pos.x - (playerW / 2);
    collider->upperBound.y = pos.y - playerH;
    collider->lowerBound.x = pos.x + (playerW / 2);
    collider->lowerBound.y = pos.y;
}

void Player::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (playerW / 2);
    player_rect.y = (int)pos.y - playerH;
    player_rect.w = playerW;
    player_rect.h = playerH;
    SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff blue
    SDL_RenderFillRect(renderer, &player_rect);

    // draw a rect representing the collider
    SDL_Color collider_color = {0xff, 0x00, 0x00,0xff};
    collider->debugRender(renderer, collider_color);

    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 6;
    debug_point_pos.h = 6;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point_pos);
}