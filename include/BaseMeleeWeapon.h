#ifndef BASEMELEEWEAPON_H
#define BASEMELEEWEAPON_H

#include "BaseProjectile.h"

class BaseDamageable;

class BaseMeleeWeapon : public BaseProjectile
{
public:
    BaseMeleeWeapon(float x, float y, float offsetX, float offsetY, BaseDamageable* damageable);

    void updatePosition(float dt) override;
    
protected:
    float offsetX;
    float offsetY;

};

#endif