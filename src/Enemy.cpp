#include "Enemy.h"

#include "AABB.h"

Enemy::Enemy(float x, float y)
{
    // initialize everything
    pos.x = x;
    pos.y = y;
    enemyW = 30;
    enemyH = 60;
    colliderW = 50;
    colliderH = 50;
    velX = 0;
    velY = 0;
    moveSpeed = 180.0f;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);
    maxHealth = 100;
    health = maxHealth;
    damageable = true;
    colliding = false;
    
    immuneTime = 0.2f; // how many seconds of iframes
    immuneTimer = immuneTime; 
}

Enemy::~Enemy()
{
    printf("Deleted enemy\n");
    delete collider;
}

void Enemy::update(float dt)
{
    if (health <= 0) { printf("enemy is dieded :(\n"); removeable = true; } // if health is below zero, set removeable flag
    else
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderW / 2);
        collider->upperBound.y = pos.y - (colliderH / 2) - (enemyH / 2);
        collider->lowerBound.x = pos.x + (colliderW / 2);
        collider->lowerBound.y = pos.y + (colliderH / 2) - (enemyH / 2);

        // set up iframes
        if (!damageable) immuneTimer -= dt;
        if (immuneTimer <= 0.0f)
        {
            immuneTimer = immuneTime; // reset to the starting value
            damageable = true;
        }
    }
}

void Enemy::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (enemyW / 2);
    player_rect.y = (int)pos.y - enemyH;
    player_rect.w = enemyW;
    player_rect.h = enemyH;
    if (damageable) SDL_SetRenderDrawColor(renderer, 0xe0, 0x26, 0x55, 0xff); // #e02655 pink red
    else SDL_SetRenderDrawColor(renderer, 0xc9, 0x5d, 0x78, 0xff); // c95d78 brighter color
    SDL_RenderFillRect(renderer, &player_rect);

    // draw a rect representing the collider
    collider->debugRender(renderer, colliding);

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
    if(damageable)
    {
        health -= damage;
        printf("enemy took %i damage\n", damage);
        printf("enemy has %i/%i hp\n", health, maxHealth);
        damageable = false; // give iframes
    }
}
