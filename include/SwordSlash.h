#ifndef SWORDSLASH_H
#define SWORDSLASH_H

#include "BaseMeleeWeapon.h"

class BaseActor;

class SwordSlash : public BaseMeleeWeapon
{
public:
    SwordSlash(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseActor* actor);

    void destroy(ProjectileManager& projectileManager) override {}
    void render(SDL_Renderer* renderer) override;
    
};

#endif