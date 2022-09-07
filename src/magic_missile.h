#ifndef MAGIC_MISSILE_H_
#define MAGIC_MISSILE_H_

#include "base_projectile.h"

class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleManager> ParticleManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class MagicMissile : public BaseProjectile
{
public:
    MagicMissile(const Vec2f& pos,
        const Vec2f& dir,
        ResourceManagerPtr resource_manager,
        ParticleManagerPtr particle_manager,
        ParticleEmitterManagerPtr particle_emitter_manager,
        BaseObject* target);

    void Update(float dt) override;

private:
    BaseObject* target_;
    float tracking_strength_;

};

#endif