#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "base_character.h"

class UiManager;
class ProjectileManager;
class InputManager;
class BaseEnemy;

typedef std::shared_ptr<ProjectileManager> ProjectileManagerPtr;

class Player : public BaseCharacter
{
public:
    Player(const Vec2f& pos,
        ResourceManagerPtr resourceManager,
        ParticleEmitterManagerPtr particle_emitter_manager,
        UiManager& ui_manager,
        ProjectileManagerPtr projectileManager);

    inline std::vector<std::string> getDebugInfo() const
    {
        std::vector<std::string> info;
        info.push_back("Health: " + std::to_string(health_) + "/" + std::to_string(max_health_));
        info.push_back("Ammo: " + std::to_string(ammo_) + "/" + std::to_string(AMMO_MAX));
        info.push_back("Ammo regen: " + std::to_string(ammo_recharge_timer_));
        info.push_back("Immune: " + std::to_string(is_immune_));
        info.push_back("Immune timer: " + std::to_string(immune_timer_));
        info.push_back("Dodges: " + std::to_string(dodge_rolls_) + "/" + std::to_string(DODGEROLLS_MAX));
        info.push_back("Dodge regen: " + std::to_string(dodge_roll_recharge_timer_));
        return info;
    }

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies);

    void TakeDamage(const Damage& damage) override;

    void Update(float dt) override;

private:
    void updateImmuneTimer(float dt);
    void updateDodgeRoll(float dt);
    void updateDodgeRollRechargeTimer(float dt);
    void updateShootingTimer(float dt);
    void updateShootingRechargeTimer(float dt);
    void updateAttackingTimer(float dt);

    ProjectileManagerPtr projectile_manager_;
    
    bool is_receiving_input_ = true;

    // immunity
    float immune_duration_; // how many iframes (in seconds though)
    float immune_timer_;

    // Dodge Roll
    bool can_dodge_roll_ = true;
    bool is_dodge_rolling_ = false;
    float dodge_roll_duration_ = 0.2f;
    float dodge_roll_timer_ = dodge_roll_duration_;
    float dodge_roll_movespeed_ = 380.0f;
    Vec2f dodge_roll_dir_;
    const int DODGEROLLS_MAX = 1;
    int dodge_rolls_ = DODGEROLLS_MAX;
    float dodge_roll_recharge_cooldown_ = 1.0f;
    float dodge_roll_recharge_timer_ = dodge_roll_recharge_cooldown_;

    // Shooting
    const int AMMO_MAX = 100;
    int ammo_ = AMMO_MAX;
    bool can_shoot_ = true;
    float shooting_cooldown_ = 0.1f; // time before able to shoot again "cool down"
    float shooting_cooldown_timer_ = 0.0f;
    float ammo_recharge_cooldown_ = 0.4f;
    float ammo_recharge_timer_ = ammo_recharge_cooldown_;

    // for targeted abilities
    BaseObject* target_;

    // Attacking
    bool can_attack_ = true;
    float attack_cooldown_ = 0.4f; // time before able to attack again "cool down"
    float attack_timer_ = 0.0f;
    
};

#endif