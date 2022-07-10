#ifndef SWORD_H
#define SWORD_H

#include "BaseProjectile.h"

class Sword : public BaseProjectile
{
public:
    Sword(float x, float y);
    ~Sword() override;

    void render(SDL_Renderer* renderer) override;
    
};

#endif