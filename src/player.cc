#include "player.h"

#include "ui_manager.h"
#include "Healthbar.h"
#include "input_manager.h"
#include "projectile_manager.h"
#include "base_enemy.h"
#include "resource_manager.h"

Player::Player(const Vec2f& pos,
    ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager,
    UiManager& ui_manager,
    ProjectileManagerPtr projectile_manager)
    : BaseCharacter(pos, resource_manager, particle_emitter_manager)
{
    // initialize everything
    name_ = "Player";

    texture_ = resource_manager_->GetTexture("player_texture");

    ui_manager.addHealthbar(16, 16, 200, 14, this);
    projectile_manager_ = projectile_manager;

    rect_.w = 30;
    rect_.h = 50;

    collider_rect_.w = 40;
    collider_rect_.h = 30;
    

    max_health_ = 80;
    health_ = max_health_;
    

    // set the resistance values
    resistance_ = {0};
    resistance_ = { .standard_resistance = 0, .crushing_resistance = 0, .fire_resistance = 0 };

    immune_duration_ = 0.2f; // how many seconds of iframes
    immune_timer_ = immune_duration_;

    movespeed_ = 150.0f;
    current_movespeed_ = movespeed_;
}

void Player::resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies)
{
    for (const auto& enemy : enemies)
    {
        if (SDL_HasIntersection(&enemy->collider_rect(), &collider_rect_))
        {
            TakeDamage(enemy->damage());
            Push(Vec2f::GetDirection(enemy->pos(), pos_), 100.0f);
        }
    }
}

void Player::handleInput(InputManager& inputManager)
{
    if (is_receiving_input_)
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
            if (can_shoot_)
            {
                int fireballVelX = (facing_direction_ == FACING_RIGHT) ? 1 : -1;
                projectile_manager_->AddFireball({ pos_.x, pos_.y - (rect_.h / 2) }, { (float)fireballVelX, 0.0f });
                can_shoot_ = false;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_X))
        {
            if (can_attack_)
            {
                float swordOffsetX = (facing_direction_ == FACING_RIGHT) ? 28.0f : -28.0f;
                can_attack_ = false;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_C))
        {
            if (can_dodge_roll_ && (dodge_rolls_ > 0))
            {
                is_receiving_input_ = false;
                can_dodge_roll_ = false;
                dodge_rolls_--;
                dodge_roll_dir_ = dir_;
                is_dodge_rolling_ = true;
            }
        }
        if (inputManager.keyPressed(SDL_SCANCODE_K))
        {
            TakeDamage({ .standard = 10, .crushing = 10, .fire = 10 });
        }

        if (inputManager.mousePressed(0))
        {
            if (can_shoot_)
            {
                // add a new fireball with some offset from the origin
                projectile_manager_->AddFireball({ pos_.x, pos_.y - (rect_.h / 2) }, Vec2f::GetDirection(pos_, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() }));

                // magiiic missile
                // Vec2f dir_to_mouse = Vec2f::GetDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() });
                // Vec2f dir_to_mouse_offset_up = Vec2f::GetDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() - 100 });
                // Vec2f dir_to_mouse_offset_down = Vec2f::GetDirection(pos, { (float)inputManager.getMouseX(), (float)inputManager.getMouseY() + 100 });
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
                can_shoot_ = false;
            }
        }
    }
}

void Player::TakeDamage(const Damage& damage)
{
    if(!is_immune_)
    {
        // set status
        if (damage.set_burning) is_on_fire_ = true;

        // take damage
        int damageTaken = resistance_.damageAfterRestistance(damage);
        health_ -= damageTaken;
        printf("%s took %i damage\n", name_.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name_.c_str(), health_, max_health_);
        is_immune_ = true; // give iframes
        is_being_hurt_ = true;
    }
}

void Player::updateImmuneTimer(float dt)
{
    // set up iframes
    if (is_immune_) 
    {
        if (immune_timer_ > 0.0f)
        {
            immune_timer_ -= dt;
        }
        else
        {
            immune_timer_ = immune_duration_; // reset to the starting value
            is_immune_ = false;
        }
    }

}

void Player::updateDodgeRoll(float dt)
{
    if (is_dodge_rolling_)
    {
        if (dodge_roll_timer_ > 0.0f)
        {
            dir_ = dodge_roll_dir_;
            current_movespeed_ = dodge_roll_movespeed_;
            is_immune_ = true;
            dodge_roll_timer_ -= dt;
        }
        else // finished dodge rolling
        {
            is_dodge_rolling_ = false;
            current_movespeed_ = movespeed_;
            dodge_roll_timer_ = dodge_roll_duration_; // reset timer
            can_dodge_roll_ = true;
            is_receiving_input_ = true; // allow input again
        }
    }
}

void Player::updateDodgeRollRechargeTimer(float dt)
{
    if (dodge_rolls_ < DODGEROLLS_MAX)
    {
        if (dodge_roll_recharge_timer_ > 0.0f)
        {
            dodge_roll_recharge_timer_ -= dt;
        }
        else
        {
            printf("regained dodgeroll!\n");
            dodge_rolls_++;
            dodge_roll_recharge_timer_ = dodge_roll_recharge_cooldown_; // reset cooldown
        }
    }
}

void Player::updateShootingTimer(float dt)
{
    if (!can_shoot_ && (ammo_ > 0)) // if we can't shoot then run a cooldown
    {
        if (shooting_cooldown_timer_ < shooting_cooldown_)
        {
            shooting_cooldown_timer_ += dt;
        }
        else
        {
            can_shoot_ = true;
            shooting_cooldown_timer_ = 0.0f; // reset cooldown to 0
        }
    }
}

void Player::updateShootingRechargeTimer(float dt)
{
    if (ammo_ < AMMO_MAX) // if we dont have maximum amount of ammo
    {
        if (ammo_recharge_timer_ > 0.0f)
        {
            ammo_recharge_timer_ -= dt;
        }
        else
        {
            printf("regained 1 ammo!\n");
            ammo_++;
            ammo_recharge_timer_ = ammo_recharge_cooldown_; // reset cooldown
        }
    }
}

void Player::updateAttackingTimer(float dt)
{
    if (!can_attack_) // if we can't attack then run a cooldown
    {
        if (attack_timer_ < attack_cooldown_)
        {
            attack_timer_ += dt;
        }
        else
        {
            can_attack_ = true;
            attack_timer_ = 0.0f; // reset cooldown to 0
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