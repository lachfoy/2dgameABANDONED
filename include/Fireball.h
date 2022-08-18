#ifndef FIREBALL_H
#define FIREBALL_H

#include "BaseProjectile.h"

class Fireball : public BaseProjectile
{
public:
    Fireball(const Vec2f& pos,
        const Vec2f& dir,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager);

    void create(ProjectileManager& projectileManager) override {}
    void destroy(ProjectileManager& projectileManager) override;

    void spawnParticles(float dt) override;
    void updatePosition(float dt) override; // override to add particle functionality
    void render(SDL_Renderer* renderer) override;

private:
    float trailSpawnTime = 0.02f;
    float trailSpawnTimer = trailSpawnTime;

};

#endif