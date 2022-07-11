#ifndef SWORD_H
#define SWORD_H

#include "BaseProjectile.h"

class BaseDamageable;

class Sword : public BaseProjectile
{
public:
    Sword(float x, float y, float offsetX, float offsetY, BaseDamageable* damageable);
    ~Sword() override;

    void updatePosition(float dt) override;
    void render(SDL_Renderer* renderer) override;
    
private:
    float offsetX;
    float offsetY;
};

#endif