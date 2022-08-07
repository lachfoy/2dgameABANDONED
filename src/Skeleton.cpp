#include "Skeleton.h"

#include "AABB.h"
#include "Player.h"
#include "UiManager.h"
#include "EnemyManager.h"

Skeleton::Skeleton(float x, float y, ResourceManager* resourceManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player)
    : BaseEnemy(x, y, resourceManager, uiManager, projectileManager, player)
{
    // initialize everything
    name = "Skeleton";
    
    width = 30;
    height = 60;

    colliderW = 40;
    colliderH = 30;

    maxHealth = 80;
    health = maxHealth;

    resistance = {0};
    resistance = { .standardResistance = 0, .crushingResistance = -80, .fireResistance = 0 };

    immuneTime = 0.1f; // how many seconds of iframes
    immuneTimer = immuneTime;

    startingMoveSpeed = 10.0f; // slowww
    moveSpeed = startingMoveSpeed;

    damage = {0};
    damage = { .crushing = 6 };

    thinkingTime = 2.0f;
    thinkingTimer = (float)((rand() % 2) + 1);
}

void Skeleton::updateAI(float dt)
{
    // do thinking. this is really messy :/
    thinkingTimer -= dt;
    if (thinkingTimer <= 0.0f)
    {
        printf("Skeleton had a thought...\n");
        targetX = player->posX;
        targetY = player->posY;
        
        thinkingTimer = thinkingTime;  // reset to the starting value
    }

    // get direction vector from pos to target
    float dirToTargetX = (targetX - posX);
    float dirToTargetY = (targetY - posY);

    // use pythag to get distance
    // d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
    float distance = sqrtf((dirToTargetX * dirToTargetX) + (dirToTargetY * dirToTargetY));

    // use distance to normalize the velocity vector
    velX = dirToTargetX / distance;
    velY = dirToTargetY / distance;
}

void Skeleton::render(SDL_Renderer* renderer)
{
    // create rect representing the enemy
    SDL_Rect enemy_rect;
    enemy_rect.x = (int)posX - (width / 2);
    enemy_rect.y = (int)posY - height;
    enemy_rect.w = width;
    enemy_rect.h = height;
    
    // set draw color
    SDL_Color enemy_color = { 0xb1, 0xb1, 0xb1, 0xff }; // grey

    // set on fire ???
    if (onFire) enemy_color = { 0xff, 0x6a, 0x0d, 0xff }; // #ff6a0d more intense fire orange

    // set alpha depending on damageable status
    if (!damageable)
    {
        enemy_color.a = 0x65;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    else SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // draw enemy
    SDL_SetRenderDrawColor(renderer, enemy_color.r, enemy_color.g, enemy_color.b, enemy_color.a);
    SDL_RenderFillRect(renderer, &enemy_rect);
}
