#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
    // initialize everything
    pos.x = x;
    pos.y = y;
    enemyW = 40;
    enemyH = 60;
    colliderW = 50;
    colliderH = 50;
    velX = 0;
    velY = 0;
    moveSpeed = 180.0f;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
    health = 100;
    damageable = true;
}

void Enemy::update(float dt)
{
    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    // move the collider as well
    collider->upperBound.x = pos.x - (colliderW / 2);
    collider->upperBound.y = pos.y - (colliderH / 2) - (enemyH / 2);
    collider->lowerBound.x = pos.x + (colliderW / 2);
    collider->lowerBound.y = pos.y + (colliderH / 2) - (enemyH / 2);
}

void Enemy::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (enemyW / 2);
    player_rect.y = (int)pos.y - enemyH;
    player_rect.w = enemyW;
    player_rect.h = enemyH;
    SDL_SetRenderDrawColor(renderer, 0xe3, 0x48, 0x36, 0xff); // #e34836 red
    SDL_RenderFillRect(renderer, &player_rect);

    // draw a rect representing the collider
    collider->debugRender(renderer);

    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 6;
    debug_point_pos.h = 6;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point_pos);
}

void Enemy::doDamage(int damage)
{
    while(damageable)
    {
        health -= damage;
    }
}
