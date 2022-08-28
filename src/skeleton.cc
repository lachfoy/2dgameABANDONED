#include "skeleton.h"

#include "AABB2i.h"
#include "player.h"
#include "UiManager.h"
#include "EnemyManager.h"
#include "resource_manager.h"

Skeleton::Skeleton(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
    UiManager& ui_manager,
    std::shared_ptr<ProjectileManager> projectile_manager,
    std::shared_ptr<Player> player)
     : BaseEnemy(pos, resource_manager, particle_manager, particle_emitter_manager, ui_manager, projectile_manager, player)
{
    // initialize everything
    name_ = "Skeleton";
    
    width_ = 30;
    height_ = 50;

    texture_ = resource_manager_->GetTexture("skeleton_texture");

    colliderW = 40;
    colliderH = 30;

    max_health_ = 80;
    health_ = max_health_;

    resistance = {0};
    resistance = { .crushingResistance = -80 };

    hurtCooldown = 0.1f; // how many seconds of iframes
    hurtTimer = hurtCooldown;

    startingMoveSpeed = 20.0f; // slowww
    moveSpeed = startingMoveSpeed;

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