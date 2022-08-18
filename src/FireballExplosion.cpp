#include "FireballExplosion.h"

#include "ProjectileManager.h"
#include "ResourceManager.h"
#include "ParticleManager.h"

FireballExplosion::FireballExplosion(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager)
     : BaseProjectile(pos, { 0.0f, 0.0f }, resourceManager, particleManager)
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

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_explosion_rect;
    fireball_explosion_rect.w = 200;
    fireball_explosion_rect.h = 200;
    fireball_explosion_rect.x = (int)pos.x - (fireball_explosion_rect.w / 2);
    fireball_explosion_rect.y = (int)pos.y - (fireball_explosion_rect.h / 2);

    SDL_RenderCopy(renderer, m_resourceManager->getTexture("FireballExplosionTexture"), NULL, &fireball_explosion_rect);

    // draw collider
    //collider.debugRender(renderer);
}