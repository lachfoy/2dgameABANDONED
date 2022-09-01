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
    resistance_ = {0};
}

void BaseCharacter::TakeDamage(const Damage& damage)
{
    if(!is_immune_)
    {
        // set status
        if (damage.setBurning && !is_on_fire_)
        {
            is_on_fire_ = true;

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
            particle_emitter_manager_->AddParticleEmitter(this, 0.01f, on_fire_duration_, 1, info);
        } 

        // take damage
        int damageTaken = resistance_.damageAfterRestistance(damage);
        health_ -= damageTaken;
        is_being_hurt_ = true;
        printf("%s took %i damage\n", name_.c_str(), damageTaken);
        if (health_ <= 0)
        {
            printf("%s died\n", name_.c_str());
            removable_ = true;
        }
        else 
        {
            printf("%s has %i/%i HP\n", name_.c_str(), health_, max_health_); 
        }
    }
}

// instead we should take in an origin pos, then do the velocity calculation.\
    we should also use some kind of calculation based on a "mass" attribute
void BaseCharacter::Push(const Vec2f& pushDir, float pushMoveSpeed)
{
    if (!is_being_pushed_)
    {
        this->push_dir_.x = pushDir.x;
        this->push_dir_.y = pushDir.y;
        this->push_movespeed_ = pushMoveSpeed;
        is_being_pushed_ = true;
    }
}

void BaseCharacter::Render(SDL_Renderer* renderer)
{
    RenderShadow(renderer);

    // set draw color
    color_ = { 0xff, 0xff, 0xff, 0xff };

    // set alpha depending on damageable status
    if (is_immune_) color_.a = 0x65;

    // set on fire ???
    if (is_on_fire_) color_ = { 0xff, 0x6a, 0x0d, 0xff }; // #ff6a0d more intense fire orange

    // owwwie
    if (is_being_hurt_) color_ = { 0xff, 0x4e, 0x45, 0xff }; // #ff4e45
    
    // draw player
    //SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    //SDL_RenderFillRect(renderer, &m_rect);
    SDL_SetTextureColorMod(texture_, color_.r, color_.g, color_.b);
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

void BaseCharacter::RenderDebug(SDL_Renderer* renderer)
{
    // draw collider rect in red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &collider_rect_);
}

void BaseCharacter::UpdatePush(float dt)
{
    // push timer
    if (is_being_pushed_)
    {
        if (push_timer_ > 0.0f)
        {
            dir_.x = push_dir_.x;
            dir_.y = push_dir_.y;
            current_movespeed_ = push_movespeed_;
            push_timer_ -= dt;
        }
        else
        {
            // reset back to normal
            is_being_pushed_ = false;
            current_movespeed_ = movespeed_;
            push_timer_ = push_duration_;
        }
    }
}

void BaseCharacter::UpdateHurt(float dt)
{
    // hurt timer
    if (is_being_hurt_)
    {
        if (hurt_timer_ > 0.0f)
        {
            hurt_timer_ -= dt;
        }
        else
        {
            hurt_timer_ = hurt_cooldown_; // reset to the starting value
            is_being_hurt_ = false;
        }
    }
}

void BaseCharacter::UpdateFire(float dt)
{
    // on fire timer
    if (can_be_set_on_fire_)
    {
        if (is_on_fire_) // they stay on fire not forever :)
        {
            if (on_fire_timer_ > 0.0f)
            {
                on_fire_timer_ -= dt;

                if (fire_tick_timer_ > 0.0f) fire_tick_timer_ -= dt;
                else
                {
                    TakeDamage(statusBurning);
                    fire_tick_timer_ = fire_tick_interval_; // reset to the starting value
                }
            }
            else
            {
                is_on_fire_ = false;
                on_fire_timer_ = on_fire_duration_;
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
    pos_.x += dir_.x * current_movespeed_ * dt;
    pos_.y += dir_.y * (current_movespeed_ * 0.7f) * dt; // moving in the Y direction is a bit slower

    // update the rect position
    rect_.x = (int)pos_.x - (rect_.w / 2);
    rect_.y = (int)pos_.y - rect_.h;

    // reset velocity
    dir_.x = 0.0f;
    dir_.y = 0.0f;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider_rect_.x = (int)pos_.x - (collider_rect_.w / 2);
    collider_rect_.y = (int)pos_.y - (collider_rect_.h / 2) - (rect_.h / 2);
}

void BaseCharacter::RenderShadow(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect shadow_rect;
    const int max_width = 60; // set a max width for damageable objects, scale the shadow rect by a % of the width to the max width
    const int shadow_default_width = 60;
    const int shadow_default_height = 24;
    shadow_rect.w = (int)(shadow_default_width * (rect_.w / (float)max_width));
    shadow_rect.h = (int)(shadow_default_height * (rect_.h / (float)max_width));
    shadow_rect.x = (int)pos_.x - (shadow_rect.w / 2);
    shadow_rect.y = (int)pos_.y - (shadow_rect.h / 2);

    // draw texture
    SDL_RenderCopy(renderer, resource_manager_->GetTexture("shadow_texture"), NULL, &shadow_rect);
}

