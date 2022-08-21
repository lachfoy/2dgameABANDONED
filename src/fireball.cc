#include "fireball.h"

#include "projectile_manager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "ResourceManager.h"

Fireball::Fireball(const Vec2f& pos,
    const Vec2f& dir, 
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager)
     : BaseProjectile(pos, dir, resource_manager, particle_manager, particle_emitter_manager)
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

    particle_emitter_manager->AddParticleEmitter(this);
}

void Fireball::OnDestroy(ProjectileManager& projectileManager)
{
    // when destroyed, create an explosion
    projectileManager.AddFireballExplosion(pos);
}

void Fireball::Update(float dt)
{
    if (lifeTime <= 0.0f)
        removable = true;
    else
        lifeTime -= dt;

    // update the internal position
    pos.x += dir.x * moveSpeed * dt;
    pos.y += dir.y * moveSpeed * dt;

    if (rotate)
    {
        if (angle >= 360)
            angle = 0.0f;
        else
            angle += rotationSpeed;
    }

    // move the particle emitter


    // move the collider as well
    collider.minX = (int)pos.x - (colliderW / 2);
    collider.minY = (int)pos.y - (colliderH / 2);
    collider.maxX = (int)pos.x + (colliderW / 2);
    collider.maxY = (int)pos.y + (colliderH / 2);
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