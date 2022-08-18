#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class UiManager;
class ProjectileManager;
class InputManager;
class BaseEnemy;

class Player : public BaseDamageable
{
public:
    Player(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<UiManager> uiManager,
        std::shared_ptr<ProjectileManager> projectileManager);

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<std::unique_ptr<BaseEnemy>>& enemies);

    void takeDamage(const Damage& damage) override;

    void updateImmuneTimer(float dt);
    void updateDodgeRoll(float dt);
    void updateDodgeRollRechargeTimer(float dt);
    void updateShootingTimer(float dt);
    void updateShootingRechargeTimer(float dt);
    void updateAttackingTimer(float dt);

    int getAmmo() const { return ammo; }
    void updatePlayer(float dt);

    void render(SDL_Renderer* renderer) override;
    void renderDebug(SDL_Renderer* renderer);

private:
    std::shared_ptr<UiManager> m_uiManager;
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
    const int AMMO_MAX = 3;
    int ammo = AMMO_MAX;
    bool canShoot = true;
    float shootingTime = 0.1f; // time before able to shoot again "cool down"
    float shootingTimer = 0.0f;
    float shootRechargeTime = 1.0f;
    float shootRechargeTimer = shootRechargeTime;

    // Attacking
    bool canAttack = true;
    float attackingTime = 0.4f; // time before able to attack again "cool down"
    float attackingTimer = 0.0f;
    
};

#endif