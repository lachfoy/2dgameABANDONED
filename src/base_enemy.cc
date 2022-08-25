#include "base_enemy.h"

#include "UiManager.h"
#include "projectile_manager.h"
#include "player.h"
#include "DynamicHealthbar.h"

BaseEnemy::BaseEnemy(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
    std::shared_ptr<UiManager> ui_manager,
    std::shared_ptr<ProjectileManager> projectile_manager,
    std::shared_ptr<Player> player)
     : BaseActor(pos, resource_manager, particle_manager, particle_emitter_manager)
{
    ui_manager_ = ui_manager;
    projectile_manager_ = projectile_manager;
    player_ = player;

    ui_manager_->addDynamicHealthbar(44, 4, this);
}

void BaseEnemy::Update(float dt)
{
    UpdateAI(dt);
    UpdateHurt(dt);
    UpdateFire(dt);
    UpdatePush(dt);
    UpdatePosition(dt);
}