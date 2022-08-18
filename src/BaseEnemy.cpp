#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
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
    this->m_uiManager = uiManager;
    this->projectileManager = projectileManager;
    this->player = player;

    m_uiManager->addDynamicHealthbar(44, 4, this);
}