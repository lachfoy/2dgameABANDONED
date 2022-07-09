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
    this->player = player; // not sure I want to give the player to every enemy or just delegate that responsibility to the enemy manager...
    //healthBar->setSize(42, 4);

    uiManager->addDynamicHealthbar(60, 5, this);
}

void BaseEnemy::updateHealthBarPosition()
{
    //healthBar->setCenterPosition(posX, posY - height - 6);
}