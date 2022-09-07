#include "base_projectile.h"

#include "particle_manager.h"
#include "resource_manager.h"
#include "particle_emitter_manager.h"

BaseProjectile::BaseProjectile(const Vec2f& pos,
    const Vec2f& dir,
    SDL_Texture* texture,
    ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager)
     : BaseObject(pos)
{
    dir_ = dir;
    texture_ = texture;
    resource_manager_ = resource_manager;
    particle_emitter_manager_ = particle_emitter_manager;
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
        rect_.x = int(pos_.x) - (rect_.w / 2);
        rect_.y = int(pos_.y) - (rect_.h / 2);

        // move the collider as well
        collider_rect_.x = (int)pos_.x - (collider_rect_.w / 2);
        collider_rect_.y = (int)pos_.y - (collider_rect_.h / 2);

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

void BaseProjectile::RenderDebug(SDL_Renderer* renderer)
{
    // draw collider rect in red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &collider_rect_);
}
