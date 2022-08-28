#ifndef ENEMY_H_
#define ENEMY_H_

#include <SDL2/SDL.h>

#include "base_enemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
        UiManager& ui_manager,
        std::shared_ptr<ProjectileManager> projectileManager,
        std::shared_ptr<Player> player);

private:
    void UpdateAI(float dt) override;

    Vec2f target;
    float thinkingTime;
    float thinkingTimer;
    
};

#endif