#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "base_projectile.h"

class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;
class ProjectileManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleManager> ParticleManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class Fireball : public BaseProjectile
{
public:
    Fireball(const Vec2f& pos,
        const Vec2f& dir,
        ResourceManagerPtr resource_manager,
        ParticleManagerPtr particle_manager,
        ParticleEmitterManagerPtr particle_emitter_manager);

    void OnDestroy(ProjectileManager& projectileManager) override;

};

#endif