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
    ~Player() override;

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void doDodgeRoll(float dt);

    void updatePlayer(float dt);

    void render(SDL_Renderer* renderer) override;

private:
    UiManager* uiManager;
    ProjectileManager* projectileManager;
    
    bool dodgeRolling = false;
    float dodgeRollTime = 0.4f;
    float dodgeRollTimer = dodgeRollTime;
    float defaultMoveSpeed = 100.0f;
    float dodgeRollMoveSpeed = 200.0f;
};

#endif