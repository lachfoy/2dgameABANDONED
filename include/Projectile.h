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

    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    float moveSpeed;
    int colliderW;
    int colliderH;
};

#endif