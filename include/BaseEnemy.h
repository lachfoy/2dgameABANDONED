#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class BaseEnemy : public BaseObject
{
public:
    BaseEnemy(float x, float y);
    virtual ~BaseEnemy(); // derived enemies can add functionality

    int damage; // public because we are laaaazy

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    AABB getCollider() const { return *collider; }

    void doDamage(int damage);
    
    void update(float dt); // derived enemies cant touch this!
    virtual void updateAI(float dt) = 0; // derived enemies can add any AI functionality if they wish 
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
    int enemyW;
    int enemyH;
    int colliderW;
    int colliderH;
    AABB* collider;
    int maxHealth;
    int health;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
    float moveSpeed;
};

#endif