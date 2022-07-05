#ifndef FIREBALL_H
#define FIREBALL_H

#include "BaseProjectile.h"

class ProjectileManager;
class Fireball : public BaseProjectile
{
public:
    Fireball(float x, float y, int velX, int velY);
    ~Fireball();

    void onDestroy(ProjectileManager& projectileManager) override;

    //inline void update(float dt); // base class handles updating
    void render(SDL_Renderer* renderer) override;

private:

};

#endif