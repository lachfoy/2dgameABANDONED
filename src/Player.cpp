#include "Player.h"

#include "AABB2i.h"
#include "UiManager.h"
#include "Healthbar.h"
#include "InputManager.h"
#include "ProjectileManager.h"
#include "BaseEnemy.h"

Player::Player(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<UiManager> uiManager,
    std::shared_ptr<ProjectileManager> projectileManager)
    : BaseActor(pos, resourceManager, nullptr)
{
    // initialize everything
    name = "Player";

    this->m_uiManager = uiManager;
    this->projectileManager = projectileManager;

    width = 30;
    height = 60;

    colliderW = 40;
    colliderH = 30;

    maxHealth = 80;
    health = maxHealth;
    m_uiManager->addHealthbar(16, 16, 200, 14, this);
    m_uiManager->addPlayerDebugText(32, 32, std::make_shared<Player>(*this)); // really messy... rework this

    // set the resistance values
    resistance = {0};
    resistance = { .standardResistance = 0, .crushingResistance = 0, .fireResistance = 0 };

    immuneCooldown = 0.2f; // how many seconds of iframes
    immuneTimer = immuneCooldown;

    startingMoveSpeed = 100.0f;
    moveSpeed = startingMoveSpeed;
}

void Player::resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (AABB2i::testOverlap(enemies[i]->getCollider(), collider))
        {
            takeDamage(enemies[i]->getDamage());
        }
    }
}

void Player::handleInput(InputManager& inputManager)
{
    if (isReceivingInput)
    {
        if (inputManager.keyPressed(SDL_SCANCODE_UP) | inputManager.keyPressed(SDL_SCANCODE_W))
            dir.y = -1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_DOWN) | inputManager.keyPressed(SDL_SCANCODE_S))
            dir.y = 1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_LEFT) | inputManager.keyPressed(SDL_SCANCODE_A))
            dir.x = -1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_RIGHT) | inputManager.keyPressed(SDL_SCANCODE_D))
            dir.x = 1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_Z))
        {
            if (canShoot)
            {
                int fireballVelX = (facingDirection == FACING_RIGHT) ? 1 : -1;
                projectileManager->addFireball({ pos.x, pos.y - (height / 2) }, { (float)fireballVelX, 0.0f });
                canShoot = false;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_X))
        {
            if (canAttack)
            {
                float swordOffsetX = (facingDirection == FACING_RIGHT) ? 28.0f : -28.0f;
                projectileManager->addSword(pos, swordOffsetX, -(height / 2) - 3.0f, this);
                canAttack = false;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_C))
        {
            if (canDodgeRoll && (dodgeRolls > 0))
            {
                isReceivingInput = false;
                canDodgeRoll = false;
                dodgeRolls--;
                dodgeRollVel = dir;
                dodgeRolling = true;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_K))
        {
            takeDamage({ .standard = 10, .crushing = 10, .fire = 10 });
        }

        if (inputManager.mousePressed(0))
        {
            if (canShoot)
            {
                // add a new fireball with some offset from the origin
                projectileManager->addFireball({ pos.x, pos.y - (height / 2) }, Vec2f::getDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() }));

                ammo--; // subtract ammo
                canShoot = false;
            }
        }
    }
}

void Player::takeDamage(const Damage& damage)
{
    if(!isImmune)
    {
        // set status
        if (damage.setBurning) isOnFire = true;

        // take damage
        int damageTaken = resistance.damageAfterRestistance(damage);
        health -= damageTaken;
        printf("%s took %i damage\n", name.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name.c_str(), health, maxHealth);
        isImmune = true; // give iframes
        isBeingHurt = true;
    }
}

void Player::updateImmuneTimer(float dt)
{
    // set up iframes
    if (isImmune) 
    {
        if (immuneTimer > 0.0f)
        {
            immuneTimer -= dt;
        }
        else
        {
            immuneTimer = immuneCooldown; // reset to the starting value
            isImmune = false;
        }
    }

}

void Player::updateDodgeRoll(float dt)
{
    if (dodgeRolling)
    {
        if (dodgeRollTimer > 0.0f)
        {
            dir = dodgeRollVel;
            moveSpeed = dodgeRollMoveSpeed;
            isImmune = true;
            dodgeRollTimer -= dt;
        }
        else // finished dodge rolling
        {
            dodgeRolling = false;
            moveSpeed = startingMoveSpeed;
            dodgeRollTimer = dodgeRollTime; // reset timer
            canDodgeRoll = true;
            isReceivingInput = true; // allow input again
        }
    }
}

void Player::updateDodgeRollRechargeTimer(float dt)
{
    if (dodgeRolls < DODGEROLLS_MAX)
    {
        if (dodgeRollRechargeTimer > 0.0f)
        {
            dodgeRollRechargeTimer -= dt;
        }
        else
        {
            printf("regained dodgeroll!\n");
            dodgeRolls++;
            dodgeRollRechargeTimer = dodgeRollRechargeTime; // reset cooldown
        }
    }
}

void Player::updateShootingTimer(float dt)
{
    if (!canShoot && (ammo > 0)) // if we can't shoot then run a cooldown
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

void Player::updateShootingRechargeTimer(float dt)
{
    if (ammo < AMMO_MAX) // if we dont have maximum amount of ammo
    {
        if (shootRechargeTimer > 0.0f)
        {
            shootRechargeTimer -= dt;
        }
        else
        {
            printf("regained 1 ammo!\n");
            ammo++;
            shootRechargeTimer = shootRechargeTime; // reset cooldown
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

void Player::update(float dt)
{
    updateFire(dt);
    updateHurt(dt);
    updatePush(dt);
    updateImmuneTimer(dt);
    updateDodgeRoll(dt);
    updateDodgeRollRechargeTimer(dt);
    updateShootingTimer(dt);
    updateShootingRechargeTimer(dt);
    updateAttackingTimer(dt);
    updatePosition(dt);
}

void Player::render(SDL_Renderer* renderer)
{
    // create rect to represent the player
    m_rect.x = (int)pos.x - (width / 2);
    m_rect.y = (int)pos.y - height;
    m_rect.w = width;
    m_rect.h = height;

    // set draw color
    m_color = { 0x29, 0x65, 0xff, 0xff }; // #2965ff blue

    // set alpha depending on damageable status
    if (isImmune) m_color.a = 0x65;

    // owwwie
    if (isBeingHurt) m_color = { 0xff, 0x4e, 0x45, 0xff }; // #ff4e45
    
    // draw player
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);
}

void Player::renderDebug(SDL_Renderer* renderer)
{
    renderCollider(renderer);
    renderOrigin(renderer);
}