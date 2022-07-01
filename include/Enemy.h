#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

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

private:
    int enemyW;
    int enemyH;
    int colliderW;
    int colliderH;
    float moveSpeed;
    int health;
    bool damageable;
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
};

#endif