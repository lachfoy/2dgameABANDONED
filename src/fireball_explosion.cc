#include "fireball_explosion.h"

#include "projectile_manager.h"
#include "ResourceManager.h"
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
}

void FireballExplosion::Render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_explosion_rect;
    fireball_explosion_rect.w = 200;
    fireball_explosion_rect.h = 200;
    fireball_explosion_rect.x = (int)pos.x - (fireball_explosion_rect.w / 2);
    fireball_explosion_rect.y = (int)pos.y - (fireball_explosion_rect.h / 2);

    SDL_RenderCopy(renderer, resource_manager_->getTexture("FireballExplosionTexture"), NULL, &fireball_explosion_rect);

    // draw collider
    //collider.debugRender(renderer);
}