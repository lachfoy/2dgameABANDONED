#ifndef FIREBALL_H
#define FIREBALL_H

#include "BaseProjectile.h"

class ProjectileManager;

class Fireball : public BaseProjectile
{
public:
    Fireball(float x, float y, int velX, int velY, ProjectileManager* projectileManager);

    void destroy() override;
    void render(SDL_Renderer* renderer) override;

private:

};

#endif