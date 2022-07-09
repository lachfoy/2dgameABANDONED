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

    enum { FACING_LEFT, FACING_RIGHT } facingDir; // public because its lazy and im late

    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void update(float dt);
    void render(SDL_Renderer* renderer) override;

private:
    UiManager* uiManager;
    ProjectileManager* projectileManager;
};

#endif