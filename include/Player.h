#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <SDL2/SDL.h>

#include "BaseDamageable.h"
#include "AABB.h"

class AABB;
class BaseEnemy;
class UIManager;
class HealthBar;
class InputManager;

class Player : public BaseDamageable
{
public:
    Player(float x, float y);
    ~Player() override;

    enum { FACING_LEFT, FACING_RIGHT } facingDir; // public because its lazy and im late

    void onCreate(UIManager& _UIManager) override;
    void onUpdate(ProjectileManager& projectileManager, float dt) override;
    void handleInput(InputManager& inputManager);

    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void render(SDL_Renderer* renderer) override;

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_MOVE_SPEED = 100
    };

    int velX = 0; // normalized x velocity
    int velY = 0; // normalized y velocity
    int playerW;
    int playerH;
    float moveSpeed;
};

#endif