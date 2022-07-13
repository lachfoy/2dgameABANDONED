#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class UiManager;
class ProjectileManager;
class InputManager;
class BaseEnemy;

class Player : public BaseDamageable
{
public:
    Player(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager);

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void updateDodgeRoll(float dt);
    void updateShootingTimer(float dt);
    void updateAttackingTimer(float dt);

    void updatePlayer(float dt);

    void render(SDL_Renderer* renderer) override;

private:
    UiManager* uiManager;
    ProjectileManager* projectileManager;
    
    // Dodge Roll
    bool dodgeRolling = false;
    float dodgeRollTime = 0.3f;
    float dodgeRollTimer = dodgeRollTime;
    float defaultMoveSpeed = 100.0f;
    float dodgeRollMoveSpeed = 340.0f;

    // Shooting
    bool canShoot = true;
    float shootingTime = 0.6f;
    float shootingTimer = 0.0f; // time before able to shoot again "cool down"

    // Attacking
    bool canAttack = true;
    float attackingTime = 0.4f;
    float attackingTimer = 0.0f; // time before able to attack again "cool down"
};

#endif