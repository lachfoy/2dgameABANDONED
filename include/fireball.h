#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "base_projectile.h"

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;

class Fireball : public BaseProjectile
{
public:
    Fireball(const Vec2f& pos,
        const Vec2f& dir,
        ResourceManagerPtr resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager);

    void OnDestroy(ProjectileManager& projectileManager) override;

};

#endif