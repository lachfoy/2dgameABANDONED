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
    name = "FireballExplosion";
    colliderW = 200;
    colliderH = 200;
    damage = {0};
    damage = { .fire = 43, .setBurning = true };
    lifeTime = 0.3f;
    removeOnCollision = false;
    onlyDamageOnce = true;
    size_ = 128;
    texture_ = resource_manager_->GetTexture("fireball_texture");
}