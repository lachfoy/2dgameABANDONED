#include "skeleton.h"

#include "AABB2i.h"
#include "player.h"
#include "UiManager.h"
#include "EnemyManager.h"
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
    
    width_ = 30;
    height_ = 50;

    texture_ = resource_manager_->GetTexture("skeleton_texture");

    collider_width_ = 40;
    collider_height_ = 30;

    max_health_ = 80;
    health_ = max_health_;

    resistance_ = {0};
    resistance_ = { .crushingResistance = -80 };

    hurt_cooldown_ = 0.1f; // how many seconds of iframes
    hurt_timer_ = hurt_cooldown_;

    movespeed_ = 20.0f; // slowww
    current_movespeed_ = movespeed_;

    damage_ = {0};
    damage_ = { .crushing = 6 };

    thinkingTime = 2.0f;
    thinkingTimer = (float)((rand() % 2) + 1);
}

void Skeleton::UpdateAI(float dt)
{
    // do thinking. this is really messy :/
    thinkingTimer -= dt;
    if (thinkingTimer <= 0.0f)
    {
        printf("Skeleton had a thought...\n");
        target = player_->pos();
        
        thinkingTimer = thinkingTime;  // reset to the starting value
    }

    dir_ = Vec2f::getDirection(pos_, target);
}