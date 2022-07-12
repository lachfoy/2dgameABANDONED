#ifndef SWORDSLASH_H
#define SWORDSLASH_H

#include "BaseMeleeWeapon.h"

class BaseDamageable;

class SwordSlash : public BaseMeleeWeapon
{
public:
    SwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* damageable);

    void render(SDL_Renderer* renderer) override;
    
};

#endif