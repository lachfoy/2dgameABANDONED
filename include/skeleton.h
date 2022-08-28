#ifndef ENEMY_H_
#define ENEMY_H_

#include <SDL2/SDL.h>

#include "base_enemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(const Vec2f& pos,
        ResourceManagerPtr resourceManager,
        ParticleEmitterManagerPtr particle_emitter_manager,
        UiManager& ui_manager,
        ProjectileManagerPtr projectileManager,
        PlayerPtr player);

private:
    void UpdateAI(float dt) override;

    Vec2f target;
    float thinkingTime;
    float thinkingTimer;
    
};

#endif