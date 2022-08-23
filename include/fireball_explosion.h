#ifndef FIREBALL_EXPLOSION_H_
#define FIREBALL_EXPLOSION_H_

#include "base_projectile.h"

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager);

};

#endif