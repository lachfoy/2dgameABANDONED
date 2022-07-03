#include "Skeleton.h"

#include "AABB.h"
#include "Player.h"

Skeleton::Skeleton(Player* player, float x, float y)
    : BaseEnemy(x, y)
{
    // initialize everything
    this->player = player;
    
    maxHealth = 100;
    immuneTime = 0.1f; // how many seconds of iframes
    moveSpeed = 40.0f; // slowww

    thinking = true;
    thinkingTime = 1.0f; // 3 seconds
    thinkingTimer = 0.0f; // instant thought
}

void Skeleton::updateAI(float dt)
{
    // do thinking. this is really messy :/
    if (thinking) thinkingTimer -= dt;
    if (thinkingTimer <= 0.0f)
    {
        thinking = false;

        if (player->pos.x > pos.x) velX = 1;
        else velX = -1;
        printf("Skeleton had a thought...\n");

        thinkingTimer = thinkingTime;  // reset to the starting value
        thinking = true;
    }
}

void Skeleton::render(SDL_Renderer* renderer)
{
    // draw the player rect representing the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (enemyW / 2);
    player_rect.y = (int)pos.y - enemyH;
    player_rect.w = enemyW;
    player_rect.h = enemyH;
    if (damageable) SDL_SetRenderDrawColor(renderer, 0xb1, 0xb1, 0xb1, 0xff); // #e02655 pink red
    else SDL_SetRenderDrawColor(renderer, 0xc9, 0x5d, 0x78, 0xff); // c95d78 pink red
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
