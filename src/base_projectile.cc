#include "base_projectile.h"

#include "BaseActor.h"
#include "particle_manager.h"
#include "resource_manager.h"
#include "particle_emitter_manager.h"

BaseProjectile::BaseProjectile(const Vec2f& pos,
    const Vec2f& dir,
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager)
     : BaseObject(pos)
{
    this->dir = dir;

    resource_manager_ = resource_manager;
    particle_manager_ = particle_manager;
    particle_emitter_manager_ = particle_emitter_manager;
    
    collider = AABB2i(pos.x, pos.y, colliderW, colliderH);
}

void BaseProjectile::Update(float dt)
{
    if (lifeTime <= 0.0f)
        removable = true;
    else
    {
        // update the internal position
        pos.x += dir.x * moveSpeed * dt;
        pos.y += dir.y * moveSpeed * dt;

        if (rotate)
        {
            angle = (angle >= 360) ? 0.0f : angle + rotationSpeed;
        }

        // update the rect for renderering
        rect_ = { int(pos.x) - int(size_ / 2), int(pos.y) - int(size_ / 2), size_, size_ };

        // move the collider as well
        collider.minX = (int)pos.x - (colliderW / 2);
        collider.minY = (int)pos.y - (colliderH / 2);
        collider.maxX = (int)pos.x + (colliderW / 2);
        collider.maxY = (int)pos.y + (colliderH / 2);

        lifeTime -= dt;
    }
}

void BaseProjectile::Render(SDL_Renderer* renderer) // should be handled by base projectile
{
    // draw the fireball
    SDL_RenderCopyEx(renderer, texture_, NULL, &rect_, angle, NULL, {});

    // draw collider
    // collider.debugRender(renderer);
}

void BaseProjectile::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider.debugRender(renderer);
}
