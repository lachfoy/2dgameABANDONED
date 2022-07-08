#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "HealthBar.h"

BaseEnemy::BaseEnemy(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player)
     : BaseDamageable(x, y, uiManager, projectileManager)
{
    this->enemyManager = enemyManager;
    this->player = player; // not sure I want to give the player to every enemy or just delegate that responsibility to the enemy manager...
    healthBar->updateSize(42, 4);
}

void BaseEnemy::updateHealthBarPosition()
{
    healthBar->updateCenterPos(posX, posY - height - 6);
}