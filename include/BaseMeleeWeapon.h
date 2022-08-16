#ifndef BASEMELEEWEAPON_H
#define BASEMELEEWEAPON_H

#include "BaseProjectile.h"

class BaseDamageable;

class BaseMeleeWeapon : public BaseProjectile
{
public:
    BaseMeleeWeapon(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder);

    // problem if this doesnt implement void destroy(ProjectileManager& projectileManager) ?
    void updatePosition(float dt) override;
    
protected:
    BaseDamageable* wielder;
    float offsetX;
    float offsetY;
    
    bool flip;

};

#endif