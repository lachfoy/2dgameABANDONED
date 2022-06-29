#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class Enemy : public BaseObject
{
public:
    Enemy(float x, float y);

    AABB* collider;

    void update(float dt);
    void render(SDL_Renderer* renderer);

    void doDamage(int damage);

private:
    float moveSpeed;
    int enemyW;
    int enemyH;
    int colliderW;
    int colliderH;
    int health;
    bool damageable;
};

#endif