#include "Skeleton.h"

#include "AABB.h"
#include "Player.h"
#include "HealthBar.h"
#include "UiManager.h"
#include "EnemyManager.h"

Skeleton::Skeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager)
    : BaseEnemy(x, y, uiManager, projectileManager, enemyManager)
{
    // initialize everything
    //this->player = player;
    
    maxHealth = 80;
    health = maxHealth;

    immuneTime = 0.1f; // how many seconds of iframes
    immuneTimer = immuneTime;

    moveSpeed = 30.0f; // slowww

    damage = 6;

    thinking = true;
    thinkingTime = 1.0f;
    thinkingTimer = thinkingTime;
}

// void Skeleton::updateAI(float dt)
// {
//     // do thinking. this is really messy :/
//     if (thinking) thinkingTimer -= dt;
//     if (thinkingTimer <= 0.0f)
//     {
//         thinking = false;

//         if (player->pos.x > pos.x) velX = 1;
//         else velX = -1;
//         printf("Skeleton had a thought...\n");

//         thinkingTimer = thinkingTime;  // reset to the starting value
//         thinking = true;
//     }
// }

void Skeleton::render(SDL_Renderer* renderer)
{
    // create rect representing the enemy
    SDL_Rect enemy_rect;
    enemy_rect.x = (int)pos.x - (enemyW / 2);
    enemy_rect.y = (int)pos.y - enemyH;
    enemy_rect.w = enemyW;
    enemy_rect.h = enemyH;
    
    // set draw color
    SDL_Color enemy_color = { 0xb1, 0xb1, 0xb1, 0xff }; // grey
    if (!damageable)
    {
        enemy_color.a = 0x65;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    else SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // draw enemy
    SDL_SetRenderDrawColor(renderer, enemy_color.r, enemy_color.g, enemy_color.b, enemy_color.a);
    SDL_RenderFillRect(renderer, &enemy_rect);

    // draw collider
    collider->debugRender(renderer);

    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 4;
    debug_point_pos.h = 4;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point_pos);
}
