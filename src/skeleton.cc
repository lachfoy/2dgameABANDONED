#include "skeleton.h"

#include "player.h"
#include "UiManager.h"
#include "enemy_manager.h"
#include "resource_manager.h"

Skeleton::Skeleton(const Vec2f& pos,
    ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager,
    UiManager& ui_manager,
    ProjectileManagerPtr projectile_manager,
    PlayerPtr player)
     : BaseEnemy(pos, resource_manager, particle_emitter_manager, ui_manager, projectile_manager, player)
{
    // initialize everything
    name_ = "Skeleton";
    
    rect_.w = 30;
    rect_.h = 50;

    texture_ = resource_manager_->GetTexture("skeleton_texture");

    collider_rect_.w = 40;
    collider_rect_.h = 30;

    max_health_ = 80;
    health_ = max_health_;

    can_be_set_on_fire_ = false; // it simply does not make sense

    resistance_ = {0};
    resistance_ = { .crushing_resistance = -80 };

    hurt_cooldown_ = 0.1f; // how many seconds of iframes
    hurt_timer_ = hurt_cooldown_;

    movespeed_ = 80.0f; // slowww
    current_movespeed_ = movespeed_;

    damage_ = {0};
    damage_ = { .crushing = 6 };

    thinking_interval_ = 2.0f;
    thinking_timer_ = (float)((rand() % 2) + 1);
}

void Skeleton::UpdateAI(float dt)
{
    // do thinking. this is really messy :/
    thinking_timer_ -= dt;
    if (thinking_timer_ <= 0.0f)
    {
        // printf("Skeleton had a thought...\n"); annoying
        target_pos_ = player_->pos();
        
        thinking_timer_ = thinking_interval_;  // reset to the starting value
    }

    dir_ = Vec2f::getDirection(pos_, target_pos_);
}