#include "BaseProjectile.h"

#include "BaseActor.h"
#include "particle_manager.h"
#include "ResourceManager.h"

BaseProjectile::BaseProjectile(const Vec2f& pos,
    const Vec2f& dir,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager)
     : BaseObject(pos)
{
    this->dir = dir;

    resource_manager_ = resourceManager;
    particle_manager_ = particleManager;
    
    collider = AABB2i(pos.x, pos.y, colliderW, colliderH);
}

void BaseProjectile::Update(float dt)
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

    // move the collider as well
    collider.minX = (int)pos.x - (colliderW / 2);
    collider.minY = (int)pos.y - (colliderH / 2);
    collider.maxX = (int)pos.x + (colliderW / 2);
    collider.maxY = (int)pos.y + (colliderH / 2);
}

void BaseProjectile::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider.debugRender(renderer);
}
