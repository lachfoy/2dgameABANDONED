#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(const Vec2f& pos, ResourceManager* resourceManager, ParticleManager* particleManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player);

    void updateAI(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    Vec2f target;
    float thinkingTime;
    float thinkingTimer;
    
};

#endif