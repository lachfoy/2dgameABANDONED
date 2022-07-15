#include "Player.h"

#include "AABB.h"
#include "UiManager.h"
#include "Healthbar.h"
#include "InputManager.h"
#include "ProjectileManager.h"
#include "BaseEnemy.h"

Player::Player(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager)
    : BaseDamageable(x, y)
{
    // initialize everything
    name = "Player";

    this->uiManager = uiManager;
    this->projectileManager = projectileManager;

    width = 30;
    height = 60;

    colliderW = 50;
    colliderH = 50;

    maxHealth = 80;
    health = maxHealth;
    uiManager->addHealthbar(16, 16, 200, 14, this);

    // set the resistance values
    resistance = {0};
    resistance = { .standardResistance = 0, .crushingResistance = 0, .fireResistance = 0 };

    immuneTime = 0.2f; // how many seconds of iframes
    immuneTimer = immuneTime;

    moveSpeed = defaultMoveSpeed;
}

void Player::resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (AABB::testOverlap(enemies[i]->getCollider(), collider))
        {
            takeDamage(enemies[i]->getDamage());
        }
    }
}

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
    if (inputManager.keyPressed(SDL_SCANCODE_Z))
    {
        if (canShoot)
        {
            int fireballVelX = (facingDirection == FACING_RIGHT) ? 1 : -1;
            projectileManager->addFireball(posX, posY - (height / 2), fireballVelX, 0);
            canShoot = false;
        }
    }
    if (inputManager.keyPressed(SDL_SCANCODE_X))
    {
        if (canAttack)
        {
            float swordOffsetX = (facingDirection == FACING_RIGHT) ? 28.0f : -28.0f;
            projectileManager->addSword(posX, posY, swordOffsetX, -(height / 2) - 3.0f, this);
            canAttack = false;
        }
    }
    if (inputManager.keyPressed(SDL_SCANCODE_C))
    {
        dodgeRolling = true;
    }
    if (inputManager.keyPressed(SDL_SCANCODE_K))
    {
        takeDamage({ .standard = 10, .crushing = 10, .fire = 10 });
    }
}

void Player::updateDodgeRoll(float dt)
{
    if (dodgeRolling)
    {
        int dodgeVelX = (facingDirection == FACING_RIGHT) ? 1 : -1;
        if (dodgeRollTimer > 0.0f)
        {
            velX = dodgeVelX;
            moveSpeed = dodgeRollMoveSpeed;
            damageable = false;
            dodgeRollTimer -= dt;
            // override input
        }
        else
        {
            dodgeRolling = false;
            moveSpeed = defaultMoveSpeed;
            dodgeRollTimer = dodgeRollTime; // reset timer
        }
    }
}

void Player::updateShootingTimer(float dt)
{
    if (!canShoot) // if we can't shoot then run a cooldown
    {
        if (shootingTimer < shootingTime)
        {
            shootingTimer += dt;
        }
        else
        {
            canShoot = true;
            shootingTimer = 0.0f; // reset cooldown to 0
        }
    }
}

void Player::updateAttackingTimer(float dt)
{
    if (!canAttack) // if we can't attack then run a cooldown
    {
        if (attackingTimer < attackingTime)
        {
            attackingTimer += dt;
        }
        else
        {
            canAttack = true;
            attackingTimer = 0.0f; // reset cooldown to 0
        }
    }
}

void Player::updatePlayer(float dt)
{
    updateDodgeRoll(dt);
    updateShootingTimer(dt);
    updateAttackingTimer(dt);
    updateImmuneTimer(dt);
    updatePosition(dt);
}

void Player::render(SDL_Renderer* renderer)
{
    // create rect to represent the player
    SDL_Rect player_rect;
    player_rect.x = (int)posX - (width / 2);
    player_rect.y = (int)posY - height;
    player_rect.w = width;
    player_rect.h = height;

    // set draw color
    SDL_Color player_color = { 0x29, 0x65, 0xff, 0xff }; // #2965ff blue

    // set alpha depending on damageable status
    if (!damageable)
    {
        player_color.a = 0x65;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    else SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // draw player
    SDL_SetRenderDrawColor(renderer, player_color.r, player_color.g, player_color.b, player_color.a);
    SDL_RenderFillRect(renderer, &player_rect);

    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 4;
    debug_point_pos.h = 4;
    debug_point_pos.x = (int)posX - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)posY - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xeb, 0xd5, 0x17, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider
    collider.debugRender(renderer);
}