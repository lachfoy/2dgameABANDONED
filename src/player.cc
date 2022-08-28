#include "player.h"

#include "AABB2i.h"
#include "UiManager.h"
#include "Healthbar.h"
#include "InputManager.h"
#include "projectile_manager.h"
#include "base_enemy.h"
#include "resource_manager.h"

Player::Player(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
    UiManager& ui_manager,
    std::shared_ptr<ProjectileManager> projectileManager)
    : BaseCharacter(pos, resourceManager, nullptr, particle_emitter_manager)
{
    // initialize everything
    name_ = "Player";

    texture_ = resource_manager_->GetTexture("main_girl_texture");

    ui_manager.addHealthbar(16, 16, 200, 14, this);
    this->projectileManager = projectileManager;

    width_ = 30;
    height_ = 50;

    colliderW = 40;
    colliderH = 30;

    max_health_ = 80;
    health_ = max_health_;
    

    // set the resistance values
    resistance = {0};
    resistance = { .standardResistance = 0, .crushingResistance = 0, .fireResistance = 0 };

    immuneCooldown = 0.2f; // how many seconds of iframes
    immuneTimer = immuneCooldown;

    startingMoveSpeed = 130.0f;
    moveSpeed = startingMoveSpeed;
}

void Player::resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (AABB2i::testOverlap(enemies[i]->collider(), collider_))
        {
            TakeDamage(enemies[i]->damage());
        }
    }
}

void Player::FindTarget(const std::vector<std::unique_ptr<BaseEnemy>>& enemies)
{
    target_ = enemies[0].get();
}

void Player::handleInput(InputManager& inputManager)
{
    if (isReceivingInput)
    {
        if (inputManager.keyPressed(SDL_SCANCODE_UP) | inputManager.keyPressed(SDL_SCANCODE_W))
            dir_.y = -1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_DOWN) | inputManager.keyPressed(SDL_SCANCODE_S))
            dir_.y = 1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_LEFT) | inputManager.keyPressed(SDL_SCANCODE_A))
            dir_.x = -1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_RIGHT) | inputManager.keyPressed(SDL_SCANCODE_D))
            dir_.x = 1.0f;
        if (inputManager.keyPressed(SDL_SCANCODE_Z))
        {
            if (canShoot)
            {
                int fireballVelX = (facing_direction_ == FACING_RIGHT) ? 1 : -1;
                projectileManager->AddFireball({ pos_.x, pos_.y - (height_ / 2) }, { (float)fireballVelX, 0.0f });
                canShoot = false;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_X))
        {
            if (canAttack)
            {
                float swordOffsetX = (facing_direction_ == FACING_RIGHT) ? 28.0f : -28.0f;
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
                dodgeRollVel = dir_;
                dodgeRolling = true;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_K))
        {
            TakeDamage({ .standard = 10, .crushing = 10, .fire = 10 });
        }

        if (inputManager.mousePressed(0))
        {
            if (canShoot)
            {
                // add a new fireball with some offset from the origin
                projectileManager->AddFireball({ pos_.x, pos_.y - (height_ / 2) }, Vec2f::getDirection(pos_, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() }));

                // magiiic missile
                // Vec2f dir_to_mouse = Vec2f::getDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() });
                // Vec2f dir_to_mouse_offset_up = Vec2f::getDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() - 100 });
                // Vec2f dir_to_mouse_offset_down = Vec2f::getDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() + 100 });
                // projectileManager->AddMagicMissile(
                //     { pos.x, pos.y - (height / 2) },
                //     dir_to_mouse,
                //     target_
                // );

                // projectileManager->AddMagicMissile(
                //     { pos.x, pos.y - (height / 2) },
                //     dir_to_mouse_offset_up,
                //     target_
                // );

                // projectileManager->AddMagicMissile(
                //     { pos.x, pos.y - (height / 2) },
                //     dir_to_mouse_offset_down,
                //     target_
                // );

                ammo_--; // subtract ammo
                canShoot = false;
            }
        }
    }
}

void Player::TakeDamage(const Damage& damage)
{
    if(!isImmune)
    {
        // set status
        if (damage.setBurning) isOnFire = true;

        // take damage
        int damageTaken = resistance.damageAfterRestistance(damage);
        health_ -= damageTaken;
        printf("%s took %i damage\n", name_.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name_.c_str(), health_, max_health_);
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
            dir_ = dodgeRollVel;
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
    if (!canShoot && (ammo_ > 0)) // if we can't shoot then run a cooldown
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
    if (ammo_ < AMMO_MAX) // if we dont have maximum amount of ammo
    {
        if (shootRechargeTimer > 0.0f)
        {
            shootRechargeTimer -= dt;
        }
        else
        {
            printf("regained 1 ammo!\n");
            ammo_++;
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

void Player::Update(float dt)
{
    UpdateFire(dt);
    UpdateHurt(dt);
    UpdatePush(dt);
    updateImmuneTimer(dt);
    updateDodgeRoll(dt);
    updateDodgeRollRechargeTimer(dt);
    updateShootingTimer(dt);
    updateShootingRechargeTimer(dt);
    updateAttackingTimer(dt);
    UpdatePosition(dt);
}