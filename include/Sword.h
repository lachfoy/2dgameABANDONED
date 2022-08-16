#ifndef SWORD_H
#define SWORD_H

#include "BaseMeleeWeapon.h"

class Sword : public BaseMeleeWeapon
{
public:
    Sword(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder);

    void destroy(ProjectileManager& projectileManager) override;
    void render(SDL_Renderer* renderer) override;
    
};

#endif