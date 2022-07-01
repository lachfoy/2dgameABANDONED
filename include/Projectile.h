#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"



class Projectile : public BaseObject
{
public:
    Projectile(float x, float y, int velX, int velY);
    ~Projectile();

    AABB* collider;

    int damage; // pack damage information into a struct so i can have different damage types?

    virtual void update(float dt);
    virtual void render(SDL_Renderer* renderer) = 0;

private:
    float moveSpeed;
    int colliderW;
    int colliderH;
    float lifeTime;

    enum
    {
        DEFAULT_LIFETIME = 1,
        DEFAULT_DAMAGE = 10,
        DEFAULT_MOVESPEED = 200
    };
};

#endif