#include "base_enemy.h"

#include "ui_manager.h"
#include "projectile_manager.h"
#include "player.h"

BaseEnemy::BaseEnemy(const Vec2f& pos,
    ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager,
    UiManager& ui_manager,
    ProjectileManagerPtr projectile_manager,
    PlayerPtr player)
     : BaseCharacter(pos, resource_manager, particle_emitter_manager)
{
    projectile_manager_ = projectile_manager;
    player_ = player;

    //ui_manager.addDynamicHealthbar(44, 4, this);
}

void BaseEnemy::Update(float dt)
{
    UpdateAI(dt);
    UpdateHurt(dt);
    UpdateFire(dt);
    UpdatePush(dt);
    UpdatePosition(dt);
}