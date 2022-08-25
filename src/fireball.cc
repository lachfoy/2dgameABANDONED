#include "fireball.h"

#include "projectile_manager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "resource_manager.h"

Fireball::Fireball(const Vec2f& pos,
    const Vec2f& dir, 
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager)
     : BaseProjectile(pos, dir, resource_manager, particle_manager, particle_emitter_manager)
{
    name_ = "Fireball";
    collider_width_ = 32;
    collider_height_ = 32;
    movespeed_ = 420.0f;
    damage_ = {0};
    damage_ = { .fire = 11 };
    lifetime_ = 1.2f;
    removeOnCollision = true;
    onlyDamageOnce = true;
    rotate_ = true;
    rotationspeed_ = 5.0f;
    size_ = 32;
    texture_ = resource_manager_->GetTexture("fireball_texture");

    ParticleSpawnInfo info;
    //info.dir
    info.random_dir = true;
    //info.movespeed
    info.movespeed_min = 20.0f;
    info.movespeed_max = 50.0f;
    info.gravity = -0.8f;
    //info.size
    info.size_min = 16;
    info.size_max = 28;
    info.color = { 255, 58, 0, 255 };
    info.texture = resource_manager_->GetTexture("flame_particle2_texture");
    //info.lifetime = 0.3f;
    info.lifetime_min = 0.1f;
    info.lifetime_max = 0.3f;
    particle_emitter_manager->AddParticleEmitter(this, 0.01f, lifetime_, 1, info);
}

void Fireball::OnDestroy(ProjectileManager& projectileManager)
{
    // when destroyed, create an explosion
    projectileManager.AddFireballExplosion(pos_);
}