#ifndef FIREBALLEXPLOSION_H
#define FIREBALLEXPLOSION_H

#include "BaseProjectile.h"

class ProjectileManager;

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(float x, float y);
    ~FireballExplosion() {}

    inline void onDestroy(ProjectileManager& projectileManager) override {}

    void render(SDL_Renderer* renderer) override;
};

#endif