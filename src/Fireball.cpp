#include "Fireball.h"

#include "ProjectileManager.h"
#include "particle_manager.h"
#include "ResourceManager.h"

Fireball::Fireball(const Vec2f& pos,
    const Vec2f& dir, 
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager)
     : BaseProjectile(pos, dir, resourceManager, particleManager)
{
    name = "Fireball";
    colliderW = 24;
    colliderH = 24;
    moveSpeed = 420.0f;
    damage = {0};
    damage = { .fire = 11 };
    lifeTime = 0.8f;
    removeOnCollision = true;
    onlyDamageOnce = true;
    rotate = true;
    rotationSpeed = 5.0f;
}

void Fireball::OnDestroy(ProjectileManager& projectileManager)
{
    // when destroyed, create an explosion
    projectileManager.AddFireballExplosion(pos);
}

void Fireball::Render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_rect;
    fireball_rect.w = 24;
    fireball_rect.h = 24;
    fireball_rect.x = (int)pos.x - (fireball_rect.w / 2);
    fireball_rect.y = (int)pos.y - (fireball_rect.h / 2);

    // draw the fireball
    SDL_RenderCopyEx(renderer, resource_manager_->getTexture("FireballTexture"), NULL, &fireball_rect, angle, NULL, {});

    // draw collider
    //collider.debugRender(renderer);
}