#ifndef FIREBALL_EXPLOSION_H_
#define FIREBALL_EXPLOSION_H_

#include "base_projectile.h"

class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleManager> ParticleManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(const Vec2f& pos,
        ResourceManagerPtr resource_manager,
        ParticleManagerPtr particle_manager,
        ParticleEmitterManagerPtr particle_emitter_manager);

};

#endif