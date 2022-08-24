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
    colliderW = 32;
    colliderH = 32;
    moveSpeed = 500.0f;
    damage = {0};
    damage = { .fire = 11 };
    lifeTime = 3.8f;
    removeOnCollision = true;
    onlyDamageOnce = true;
    rotate = true;
    rotationSpeed = 5.0f;

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
    if (lifeTime <= 0.0f)
        removable_ = true;
    else
        lifeTime -= dt;

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
        if (dir.x < target_dir.x && dir.y > target_dir.y)
        {
            dir.x += tracking_strength_;
            dir.y -= tracking_strength_;
        }
        else if (dir.x > target_dir.x && dir.y < target_dir.y)
        {
            dir.x -= tracking_strength_;
            dir.y += tracking_strength_;
        }
    }

    // update the internal position
    pos_.x += dir.x * moveSpeed * dt;
    pos_.y += dir.y * moveSpeed * dt;

    if (rotate)
    {
        if (angle >= 360)
            angle = 0.0f;
        else
            angle += rotationSpeed;
    }

    // move the collider as well
    collider.minX = (int)pos_.x - (colliderW / 2);
    collider.minY = (int)pos_.y - (colliderH / 2);
    collider.maxX = (int)pos_.x + (colliderW / 2);
    collider.maxY = (int)pos_.y + (colliderH / 2);
}


void MagicMissile::Render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    const int tex_size = 20;
    const SDL_Rect tex_rect = { (int)pos_.x - (tex_size / 2), (int)pos_.y - (tex_size / 2), tex_size, tex_size };

    // draw the MagicMissile
    SDL_RenderCopyEx(renderer, resource_manager_->GetTexture("magic_texture"), NULL, &tex_rect, angle, NULL, {});

    // draw collider
    //collider.debugRender(renderer);
}