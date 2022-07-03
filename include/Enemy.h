#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseObject.h"

class AABB;

class Enemy : public BaseObject
{
public:
    Enemy(float x, float y);
    ~Enemy();

    AABB* collider;
    bool colliding;

    void update(float dt);
    void render(SDL_Renderer* renderer);

    void doDamage(int damage);
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

private:
    int enemyW;
    int enemyH;
    int colliderW;
    int colliderH;
    float moveSpeed;
    int health;
    int maxHealth;
    bool damageable;
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
};

#endif