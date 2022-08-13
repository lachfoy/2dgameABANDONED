#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "DynamicHealthbar.h"

BaseEnemy::BaseEnemy(float x, float y, ResourceManager* resourceManager, ParticleManager* particleManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player)
     : BaseDamageable(x, y, resourceManager, particleManager)
{
    this->m_uiManager = uiManager;
    this->projectileManager = projectileManager;
    this->player = player;

    m_uiManager->addDynamicHealthbar(44, 4, this);
}