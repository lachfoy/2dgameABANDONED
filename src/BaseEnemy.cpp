#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "DynamicHealthbar.h"

BaseEnemy::BaseEnemy(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player)
     : BaseDamageable(x, y)
{
    this->uiManager = uiManager;
    this->projectileManager = projectileManager;
    this->enemyManager = enemyManager;
    this->player = player;

    uiManager->addDynamicHealthbar(44, 4, this);
}