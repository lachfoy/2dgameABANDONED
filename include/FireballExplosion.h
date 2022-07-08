#ifndef FIREBALLEXPLOSION_H
#define FIREBALLEXPLOSION_H

#include "BaseProjectile.h"

class ProjectileManager;

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(float x, float y, ProjectileManager* projectileManager);
    ~FireballExplosion() {}

    void render(SDL_Renderer* renderer) override;
};

#endif