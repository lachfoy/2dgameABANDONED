#include "base_character.h"

#include "resource_manager.h"
#include "particle_emitter_manager.h"

BaseCharacter::BaseCharacter(const Vec2f& pos,
    ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager)
     : BaseObject(pos)
{
    resource_manager_ = resource_manager;
    texture_ = nullptr;
    particle_emitter_manager_ = particle_emitter_manager;
    collider_ = AABB2i(pos_.x, pos_.y, colliderW, colliderH);
    resistance = {0};
}

void BaseCharacter::TakeDamage(const Damage& damage)
{
    if(!isImmune)
    {
        // set status
        if (damage.setBurning)
        {
            isOnFire = true;

            // add flame emitter
            ParticleSpawnInfo info;
            //info.dir
            info.random_dir = true;
            //info.movespeed
            info.movespeed_min = 40.0f;
            info.movespeed_max = 80.0f;
            info.gravity = -0.8f;
            //info.size
            info.size_min = 64;
            info.size_max = 80;
            info.color = { 255, 58, 0, 255 };
            info.texture = resource_manager_->GetTexture("flame_particle2_texture");
            //info.lifetime = 0.3f;
            info.lifetime_min = 0.1f;
            info.lifetime_max = 0.3f;
            particle_emitter_manager_->AddParticleEmitter(this, 0.01f, fireTime, 1, info);
        } 

        // take damage
        int damageTaken = resistance.damageAfterRestistance(damage);
        health_ -= damageTaken;
        printf("%s took %i damage\n", name_.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name_.c_str(), health_, max_health_);
        isBeingHurt = true;
    }
}

// instead we should take in an origin pos, then do the velocity calculation.\
    we should also use some kind of calculation based on a "mass" attribute
void BaseCharacter::Push(const Vec2f& pushDir, float pushMoveSpeed)
{
    if (!isBeingPushed)
    {
        this->pushDir.x = pushDir.x;
        this->pushDir.y = pushDir.y;
        this->pushMoveSpeed = pushMoveSpeed;
        isBeingPushed = true;
    }
}

void BaseCharacter::Render(SDL_Renderer* renderer)
{
    RenderShadow(renderer);

    // create rect to represent the player
    rect_.x = (int)pos_.x - (width_ / 2);
    rect_.y = (int)pos_.y - height_;
    rect_.w = width_;
    rect_.h = height_;

    // set draw color
    color_ = { 0xff, 0xff, 0xff, 0xff };

    // set alpha depending on damageable status
    if (isImmune) color_.a = 0x65;

    // set on fire ???
    if (isOnFire) color_ = { 0xff, 0x6a, 0x0d, 0xff }; // #ff6a0d more intense fire orange

    // owwwie
    if (isBeingHurt) color_ = { 0xff, 0x4e, 0x45, 0xff }; // #ff4e45
    
    // draw player
    //SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    //SDL_RenderFillRect(renderer, &m_rect);
    SDL_SetTextureColorMod(texture_, color_.r, color_.g, color_.b);
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

void BaseCharacter::RenderDebug(SDL_Renderer* renderer)
{
    RenderCollider(renderer);
}

void BaseCharacter::UpdatePush(float dt)
{
    // push timer
    if (isBeingPushed)
    {
        if (pushTimer > 0.0f)
        {
            dir_.x = pushDir.x;
            dir_.y = pushDir.y;
            moveSpeed = pushMoveSpeed;
            pushTimer -= dt;
        }
        else
        {
            // reset back to normal
            isBeingPushed = false;
            moveSpeed = startingMoveSpeed;
            pushTimer = pushTime;
        }
    }
}

void BaseCharacter::UpdateHurt(float dt)
{
    // hurt timer
    if (isBeingHurt)
    {
        if (hurtTimer > 0.0f)
        {
            hurtTimer -= dt;
        }
        else
        {
            hurtTimer = hurtCooldown; // reset to the starting value
            isBeingHurt = false;
        }
    }
}

void BaseCharacter::UpdateFire(float dt)
{
    // on fire timer
    if (canBeSetOnFire)
    {
        if (isOnFire) // they stay on fire not forever :)
        {
            if (fireTimer > 0.0f)
            {
                fireTimer -= dt;

                if (fireTickTimer > 0.0f) fireTickTimer -= dt;
                else
                {
                    TakeDamage(statusBurning);
                    fireTickTimer = fireTickTime; // reset to the starting value
                }
            }
            else
            {
                isOnFire = false;
                fireTimer = fireTime;
            }
        }
    }
}

void BaseCharacter::UpdatePosition(float dt)
{
    // update facing direction
    if (dir_.x > 0.0f)
        facing_direction_ = FACING_RIGHT;
    else if (dir_.x < 0.0f)
        facing_direction_ = FACING_LEFT;

    // update the internal position
    pos_.x += dir_.x * moveSpeed * dt;
    pos_.y += dir_.y * (moveSpeed * 0.7f) * dt; // moving in the Y direction is a bit slower

    // reset velocity
    dir_.x = 0.0f;
    dir_.y = 0.0f;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider_.minX = (int)pos_.x - (colliderW / 2);
    collider_.minY = (int)pos_.y - (colliderH / 2) - (height_ / 2);
    collider_.maxX = (int)pos_.x + (colliderW / 2);
    collider_.maxY = (int)pos_.y + (colliderH / 2) - (height_ / 2);
}

void BaseCharacter::RenderShadow(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect shadow_rect;
    const int max_width = 60; // set a max width for damageable objects, scale the shadow rect by a % of the width to the max width
    const int shadow_default_width = 60;
    const int shadow_default_height = 24;
    shadow_rect.w = (int)(shadow_default_width * (width_ / (float)max_width));
    shadow_rect.h = (int)(shadow_default_height * (width_ / (float)max_width));
    shadow_rect.x = (int)pos_.x - (shadow_rect.w / 2);
    shadow_rect.y = (int)pos_.y - (shadow_rect.h / 2);

    // draw texture
    SDL_RenderCopy(renderer, resource_manager_->GetTexture("ShadowTexture"), NULL, &shadow_rect);
}

void BaseCharacter::RenderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider_.debugRender(renderer);
}

