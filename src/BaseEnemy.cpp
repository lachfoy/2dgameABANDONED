#include "BaseEnemy.h"

#include "UiManager.h"
#include "projectile_manager.h"
#include "Player.h"
#include "DynamicHealthbar.h"

BaseEnemy::BaseEnemy(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager,
    std::shared_ptr<UiManager> uiManager,
    std::shared_ptr<ProjectileManager> projectileManager,
    std::shared_ptr<Player> player)
     : BaseActor(pos, resourceManager, particleManager)
{
    this->ui_manager_ = uiManager;
    this->projectileManager = projectileManager;
    this->player = player;

    ui_manager_->addDynamicHealthbar(44, 4, this);
}

void BaseEnemy::update(float dt)
{
    updateAI(dt);
    updateHurt(dt);
    updateFire(dt);
    updatePush(dt);
    updatePosition(dt);
}