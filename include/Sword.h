#ifndef SWORD_H
#define SWORD_H

#include "BaseMeleeWeapon.h"

class Sword : public BaseMeleeWeapon
{
public:
    Sword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);

    void destroy(ProjectileManager& projectileManager) override;
    void render(SDL_Renderer* renderer) override;
    
};

#endif