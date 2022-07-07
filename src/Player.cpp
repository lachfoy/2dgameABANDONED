#include "Player.h"

#include "UIManager.h"
#include "HealthBar.h"
#include "InputManager.h"

Player::Player(UIManager& _UIManager, float x, float y) : BaseDamageable(_UIManager, x, y)
{
    // initialize everything
    name = "Player";

    playerW = DEFAULT_W;
    playerH = DEFAULT_H;
    
    moveSpeed = (float)DEFAULT_MOVE_SPEED;
}

Player::~Player()
{
}

// void Player::resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies)
// {
//     for (int i = 0; i < enemies.size(); i++)
//     {
//         if (AABB::testOverlap(enemies[i]->getCollider(), *collider))
//         {
//             doDamage(enemies[i]->getDamage());
//         }
//     }
// }

void Player::handleInput(InputManager& inputManager)
{
    if (inputManager.keyPressed(SDL_SCANCODE_UP) | inputManager.keyPressed(SDL_SCANCODE_W))
        velY = -1;
    if (inputManager.keyPressed(SDL_SCANCODE_DOWN) | inputManager.keyPressed(SDL_SCANCODE_S))
        velY = 1;
    if (inputManager.keyPressed(SDL_SCANCODE_LEFT) | inputManager.keyPressed(SDL_SCANCODE_A))
        velX = -1;
    if (inputManager.keyPressed(SDL_SCANCODE_RIGHT) | inputManager.keyPressed(SDL_SCANCODE_D))
        velX = 1;
    if (inputManager.keyDown(SDL_SCANCODE_SPACE) | inputManager.keyDown(SDL_SCANCODE_Z))
    {
        
    }
}

void Player::onUpdate(float dt)
{
    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    velX = 0;
    velY = 0;

    // move the collider as well
    collider->upperBound.x = pos.x - (colliderW / 2);
    collider->upperBound.y = pos.y - (colliderH / 2) - (playerH / 2);
    collider->lowerBound.x = pos.x + (colliderW / 2);
    collider->lowerBound.y = pos.y + (colliderH / 2) - (playerH / 2);
}

void Player::render(SDL_Renderer* renderer)
{
    // create rect to represent the player
    SDL_Rect player_rect;
    player_rect.x = (int)pos.x - (playerW / 2);
    player_rect.y = (int)pos.y - playerH;
    player_rect.w = playerW;
    player_rect.h = playerH;

    // set draw color
    SDL_Color player_color = { 0x29, 0x65, 0xff, 0xff }; // #2965ff blue
    if (!damageable)
    {
        player_color.a = 0x65;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    else SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // draw player
    SDL_SetRenderDrawColor(renderer, player_color.r, player_color.g, player_color.b, player_color.a);
    SDL_RenderFillRect(renderer, &player_rect);

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