#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class EnemyManager;

class BaseEnemy : public BaseDamageable
{
public:
    BaseEnemy(float x, float y);
    virtual ~BaseEnemy(); // derived enemies can add functionality

    AABB getCollider() const { return *collider; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getDamage() const { return damage; }

    void doDamage(int damage);
    
    virtual void onDestroy(EnemyManager& enemyManager) = 0;
    virtual void updateAI(float dt) = 0; // derived enemies can add any AI functionality if they wish 
    
    void update(float dt); // derived enemies cant touch this!
    virtual void render(SDL_Renderer* renderer) = 0; // derived enemies MUST provide an implementation for renderering

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_DAMAGE = 10,
        DEFAULT_IMMUNE_TIME = 1,
        DEFAULT_MOVE_SPEED = 200
    };

protected:
    int enemyW = DEFAULT_W;
    int enemyH = DEFAULT_H;
    int colliderW = DEFAULT_COLLIDER_W;
    int colliderH = DEFAULT_COLLIDER_H;
    AABB* collider = nullptr;
    int maxHealth = DEFAULT_MAX_HEALTH;
    int health = DEFAULT_MAX_HEALTH;
    HealthBar* healthBar = nullptr;
    int damage = DEFAULT_DAMAGE;
    bool damageable = true; // if not damageable then they are taking damage
    float immuneTimer = (float)DEFAULT_IMMUNE_TIME;
    float immuneTime = 0.0f; // how many iframes (in seconds though)
    int velX = 0; // normalized x velocity
    int velY = 0; // normalized y velocity
    float moveSpeed = (float)DEFAULT_MOVE_SPEED;
};

#endif