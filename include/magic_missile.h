#ifndef MAGIC_MISSILE_H_
#define MAGIC_MISSILE_H_

#include "base_projectile.h"

class MagicMissile : public BaseProjectile
{
public:
    MagicMissile(const Vec2f& pos,
        const Vec2f& dir,
        std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
        BaseObject* target);

    void Update(float dt) override;

private:
    BaseObject* target_;
    float tracking_strength_;

};

#endif