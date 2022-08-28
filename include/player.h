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

class Player : public BaseCharacter
{
public:
    Player(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
        UiManager& ui_manager,
        std::shared_ptr<ProjectileManager> projectileManager);

    inline std::vector<std::string> getDebugInfo() const
    {
        std::vector<std::string> info;
        info.push_back("Health: " + std::to_string(health_) + "/" + std::to_string(max_health_));
        info.push_back("Ammo: " + std::to_string(ammo_) + "/" + std::to_string(AMMO_MAX));
        info.push_back("Ammo regen: " + std::to_string(shootRechargeTimer));
        info.push_back("Immune: " + std::to_string(is_immune_));
        info.push_back("Immune timer: " + std::to_string(immuneTimer));
        info.push_back("Dodges: " + std::to_string(dodgeRolls) + "/" + std::to_string(DODGEROLLS_MAX));
        info.push_back("Dodge regen: " + std::to_string(dodgeRollRechargeTimer));
        return info;
    }

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies);
    void FindTarget(const std::vector<std::unique_ptr<BaseEnemy>>& enemies);

    void TakeDamage(const Damage& damage) override;

    void Update(float dt) override;

private:
    void updateImmuneTimer(float dt);
    void updateDodgeRoll(float dt);
    void updateDodgeRollRechargeTimer(float dt);
    void updateShootingTimer(float dt);
    void updateShootingRechargeTimer(float dt);
    void updateAttackingTimer(float dt);

    std::shared_ptr<UiManager> ui_manager_;
    std::shared_ptr<ProjectileManager> projectileManager;
    
    bool isReceivingInput = true;

    // immunity
    float immuneCooldown; // how many iframes (in seconds though)
    float immuneTimer;

    // Dodge Roll
    bool canDodgeRoll = true;
    bool dodgeRolling = false;
    float dodgeRollTime = 0.2f;
    float dodgeRollTimer = dodgeRollTime;
    float dodgeRollMoveSpeed = 380.0f;
    Vec2f dodgeRollVel;
    const int DODGEROLLS_MAX = 1;
    int dodgeRolls = DODGEROLLS_MAX;
    float dodgeRollRechargeTime = 1.0f;
    float dodgeRollRechargeTimer = dodgeRollRechargeTime;

    // Shooting
    const int AMMO_MAX = 10;
    int ammo_ = AMMO_MAX;
    bool canShoot = true;
    float shootingTime = 0.1f; // time before able to shoot again "cool down"
    float shootingTimer = 0.0f;
    float shootRechargeTime = 1.0f;
    float shootRechargeTimer = shootRechargeTime;

    // for targeted abilities
    BaseObject* target_;

    // Attacking
    bool canAttack = true;
    float attackingTime = 0.4f; // time before able to attack again "cool down"
    float attackingTimer = 0.0f;
    
};

#endif