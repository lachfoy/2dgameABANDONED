#ifndef FIREBALLEXPLOSION_H
#define FIREBALLEXPLOSION_H

#include "BaseProjectile.h"

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(float x, float y);
    ~FireballExplosion() override {}

    void render(SDL_Renderer* renderer) override;
};

#endif