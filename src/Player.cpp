#include "Player.h"

#include "AABB.h"

Player::Player(float x, float y)
{
    // initialize everything
    pos.x = x;
    pos.y = y;
    velX = 0;
    velY = 0;

    playerW = DEFAULT_W;
    playerH = DEFAULT_H;
    colliderW = DEFAULT_COLLIDER_W;
    colliderH = DEFAULT_COLLIDER_H;
    collider = new AABB(pos.x, pos.y, colliderW, colliderH);

    maxHealth = DEFAULT_MAX_HEALTH;
    health = maxHealth;
    damageable = true;
    immuneTime = 0.2f; // how many seconds of iframes
    immuneTimer = immuneTime;

    moveSpeed = (float)DEFAULT_MOVE_SPEED;
}

Player::~Player()
{
    delete collider;
}

void Player::update(float dt)
{
    if (health <= 0) printf("Player is dead\n");
    else
    {
        // update the internal position
        pos.x += velX * moveSpeed * dt;
        pos.y += velY * moveSpeed * dt;

        // move the collider as well
        collider->upperBound.x = pos.x - (colliderW / 2);
        collider->upperBound.y = pos.y - (colliderH / 2) - (playerH/2);
        collider->lowerBound.x = pos.x + (colliderW / 2);
        collider->lowerBound.y = pos.y + (colliderH / 2) - (playerH/2);
    
        // set up iframes
        if (!damageable) immuneTimer -= dt;
        if (immuneTimer <= 0.0f)
        {
            immuneTimer = immuneTime; // reset to the starting value
            damageable = true;
        }
    }
}

void Player::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (playerW / 2);
    player_rect.y = (int)pos.y - playerH;
    player_rect.w = playerW;
    player_rect.h = playerH;
    if (damageable) SDL_SetRenderDrawColor(renderer, 0x29, 0x65, 0xff, 0xff); // #2965ff blue
    else SDL_SetRenderDrawColor(renderer, 0xc9, 0x5d, 0x78, 0xff); // c95d78 brighter color
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

void Player::doDamage(int damage)
{
    if(damageable)
    { 
        health -= damage;
        printf("Player took %i damage\n", damage);
        printf("Player has %i/%i HP\n", health, maxHealth);
        damageable = false; // give iframes
    }
}