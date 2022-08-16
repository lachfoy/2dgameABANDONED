#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "DynamicHealthbar.h"

BaseEnemy::BaseEnemy(const Vec2f& pos, std::shared_ptr<ResourceManager> resourceManager, ParticleManager* particleManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player)
     : BaseDamageable(pos, resourceManager, particleManager)
{
    this->m_uiManager = uiManager;
    this->projectileManager = projectileManager;
    this->player = player;

    m_uiManager->addDynamicHealthbar(44, 4, this);
}