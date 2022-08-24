#include "magic_missile.h"

#include "projectile_manager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "resource_manager.h"

MagicMissile::MagicMissile(const Vec2f& pos,
    const Vec2f& dir, 
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
    BaseObject* target)
     : BaseProjectile(pos, dir, resource_manager, particle_manager, particle_emitter_manager)
{
    target_ = target;
    tracking_strength_ = 0.01f;

    name_ = "MagicMissile";
    collider_width_ = 32;
    collider_height_ = 32;
    movespeed_ = 500.0f;
    damage_ = {0};
    damage_ = { .fire = 11 };
    lifetime_ = 3.8f;
    removeOnCollision = true;
    onlyDamageOnce = true;
    rotate_ = true;
    rotationspeed_ = 5.0f;

    ParticleSpawnInfo info;
    //info.dir
    info.random_dir = true;
    //info.movespeed
    info.movespeed_min = 20.0f;
    info.movespeed_max = 50.0f;
    info.gravity = -0.8f;
    //info.size
    info.size_min = 8;
    info.size_max = 16;
    info.color = { 0, 129, 235, 255 }; // blue
    info.texture = resource_manager_->GetTexture("flame_particle2_texture");
    //info.lifetime = 0.3f;
    info.lifetime_min = 0.1f;
    info.lifetime_max = 0.2f;
    particle_emitter_manager->AddParticleEmitter(this, 0.0f, 10.0f, 1, info);
}

void MagicMissile::Update(float dt)
{
    if (lifetime_ <= 0.0f)
        removable_ = true;
    else
        lifetime_ -= dt;

    // update dir according to target
    if (target_)
    {
        Vec2f target_dir = Vec2f::getDirection(pos_, target_->pos());
        // can overshoot
        //dir.x += (dir.x < target_dir.x) ? tracking_strength_ : -tracking_strength_;
        //dir.y += (dir.y < target_dir.y) ? tracking_strength_ : -tracking_strength_;

        // if (dir.x < target_dir.x && dir.y < target_dir.y)
        // {
        //     dir.x += tracking_strength_;
        //     dir.y += tracking_strength_;
        // }
        // else if (dir.x > target_dir.x && dir.y > target_dir.y)
        // {
        //     dir.x -= tracking_strength_;
        //     dir.y -= tracking_strength_;
        // }
        // this is a problem...
        if (dir_.x < target_dir.x && dir_.y > target_dir.y)
        {
            dir_.x += tracking_strength_;
            dir_.y -= tracking_strength_;
        }
        else if (dir_.x > target_dir.x && dir_.y < target_dir.y)
        {
            dir_.x -= tracking_strength_;
            dir_.y += tracking_strength_;
        }
    }

    // update the internal position
    pos_.x += dir_.x * movespeed_ * dt;
    pos_.y += dir_.y * movespeed_ * dt;

    if (rotate_)
    {
        if (angle_ >= 360)
            angle_ = 0.0f;
        else
            angle_ += rotationspeed_;
    }

    // move the collider as well
    collider_.minX = (int)pos_.x - (collider_width_ / 2);
    collider_.minY = (int)pos_.y - (collider_height_ / 2);
    collider_.maxX = (int)pos_.x + (collider_width_ / 2);
    collider_.maxY = (int)pos_.y + (collider_height_ / 2);
}


void MagicMissile::Render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    const int tex_size = 20;
    const SDL_Rect tex_rect = { (int)pos_.x - (tex_size / 2), (int)pos_.y - (tex_size / 2), tex_size, tex_size };

    // draw the MagicMissile
    SDL_RenderCopyEx(renderer, resource_manager_->GetTexture("magic_texture"), NULL, &tex_rect, angle_, NULL, {});

    // draw collider
    //collider.debugRender(renderer);
}