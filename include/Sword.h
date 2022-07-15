#ifndef SWORD_H
#define SWORD_H

#include "BaseMeleeWeapon.h"

class BaseDamageable;

class Sword : public BaseMeleeWeapon
{
public:
    Sword(float x, float y, float offsetX, float offsetY, ProjectileManager* projectileManager, BaseDamageable* damageable);

    void destroy() override;
    void render(SDL_Renderer* renderer) override;
    
};

#endif