#include "base_projectile.h"

#include "base_character.h"
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
    this->dir_ = dir;

    resource_manager_ = resource_manager;
    particle_manager_ = particle_manager;
    particle_emitter_manager_ = particle_emitter_manager;
    
    collider_ = AABB2i(pos.x, pos.y, collider_width_, collider_height_);
}

void BaseProjectile::Update(float dt)
{
    if (lifetime_ <= 0.0f)
        removable_ = true;
    else
    {
        // update the internal position
        pos_.x += dir_.x * movespeed_ * dt;
        pos_.y += dir_.y * movespeed_ * dt;

        if (rotate_)
        {
            angle_ = (angle_ >= 360) ? 0.0f : angle_ + rotationspeed_;
        }

        // update the rect for renderering
        rect_ = { int(pos_.x) - int(size_ / 2), int(pos_.y) - int(size_ / 2), size_, size_ };

        // move the collider as well
        collider_.minX = (int)pos_.x - (collider_width_ / 2);
        collider_.minY = (int)pos_.y - (collider_height_ / 2);
        collider_.maxX = (int)pos_.x + (collider_width_ / 2);
        collider_.maxY = (int)pos_.y + (collider_height_ / 2);

        lifetime_ -= dt;
    }
}

void BaseProjectile::Render(SDL_Renderer* renderer) // should be handled by base projectile
{
    // draw the fireball
    SDL_RenderCopyEx(renderer, texture_, NULL, &rect_, angle_, NULL, {});

    // draw collider
    // collider.debugRender(renderer);
}

void BaseProjectile::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider_.debugRender(renderer);
}
