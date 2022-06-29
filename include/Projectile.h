#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class Projectile : public BaseObject
{
public:
    Projectile(float x, float y, int velX, int velY);

    AABB* collider;

    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    float moveSpeed;
    int colliderW;
    int colliderH;
};

#endif