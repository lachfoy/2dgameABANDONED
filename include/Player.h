#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <cmath> // ONLY USED FOR CALC PYTHAG IN ONE PLACE

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class UiManager;
class ProjectileManager;
class InputManager;
class BaseEnemy;

class Player : public BaseDamageable
{
public:
    Player(float x, float y, ResourceManager* resourceManager, UiManager* uiManager, ProjectileManager* projectileManager);

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void updateDodgeRoll(float dt);
    void updateShootingTimer(float dt);
    void updateShootingRechargeTimer(float dt);
    void updateAttackingTimer(float dt);

    void updatePlayer(float dt);

    void render(SDL_Renderer* renderer) override;
    void renderDebug(SDL_Renderer* renderer);

private:
    UiManager* uiManager;
    ProjectileManager* projectileManager;
    
    // Dodge Roll
    bool dodgeRolling = false;
    float dodgeRollTime = 0.3f;
    float dodgeRollTimer = dodgeRollTime;
    float dodgeRollMoveSpeed = 340.0f;

    // Shooting
    const int AMMO_MAX = 3;
    int ammo = AMMO_MAX;
    bool canShoot = true;
    float shootingTime = 0.1f; // time before able to shoot again "cool down"
    float shootingTimer = 0.0f;
    float shootRechargeTime = 2.0f;
    float shootRechargeTimer = shootRechargeTime;

    // Attacking
    bool canAttack = true;
    float attackingTime = 0.4f; // time before able to attack again "cool down"
    float attackingTimer = 0.0f;
    
};

#endif