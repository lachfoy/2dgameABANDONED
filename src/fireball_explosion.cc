#include "fireball_explosion.h"

#include "projectile_manager.h"
#include "resource_manager.h"
#include "particle_manager.h"

FireballExplosion::FireballExplosion(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager)
     : BaseProjectile(pos, { 0.0f, 0.0f }, resource_manager, particle_manager, particle_emitter_manager)
{
    name_ = "FireballExplosion";

    collider_rect_.w = 120;
    collider_rect_.h = 120;

    damage_ = {0};
    damage_ = { .fire = 43, .set_burning = true };
    lifetime_ = 0.3f;
    removeOnCollision = false;
    onlyDamageOnce = true;
    rect_.w = 128;
    rect_.h = 128;
    texture_ = resource_manager_->GetTexture("fireball_texture");
}