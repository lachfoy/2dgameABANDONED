#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager,
        std::shared_ptr<UiManager> uiManager,
        std::shared_ptr<ProjectileManager> projectileManager,
        std::shared_ptr<Player> player);

    void updateAI(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    Vec2f target;
    float thinkingTime;
    float thinkingTimer;
    
};

#endif