#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class AABB;
class BaseEnemy;
class HealthBar;

class Player : public BaseObject
{
public:
    Player(HealthBar* healthBar, float x, float y);
    ~Player();

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    AABB getCollider() const { return *collider; }

    void doDamage(int damage);
    void resolveEnemyCollisions(const std::vector<BaseEnemy*>& enemies);

    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_IMMUNE_TIME = 1,
        DEFAULT_MOVE_SPEED = 200
    };

    int playerW;
    int playerH;
    int colliderW;
    int colliderH;
    AABB* collider;
    int maxHealth;
    int health;
    HealthBar* healthBar;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
    float moveSpeed;
};

#endif