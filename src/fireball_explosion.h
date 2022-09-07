#ifndef FIREBALL_EXPLOSION_H_
#define FIREBALL_EXPLOSION_H_

#include "base_projectile.h"

class ResourceManager;
class ParticleEmitterManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(const Vec2f& pos,
        SDL_Texture* texture,
        ResourceManagerPtr resource_manager,
        ParticleEmitterManagerPtr particle_emitter_manager);

};

#endif