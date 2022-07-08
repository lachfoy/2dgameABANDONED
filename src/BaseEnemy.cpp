#include "BaseEnemy.h"

#include "UiManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"

BaseEnemy::BaseEnemy(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player)
     : BaseDamageable(x, y, uiManager, projectileManager)
{
    this->enemyManager = enemyManager;
    this->player = player; // not sure I want to give the player to every enemy or just delegate that responsibility to the enemy manager...
}

void BaseEnemy::update(float dt)
{
    updateHealth(dt);

    // update the internal position
    pos.x += velX * moveSpeed * dt;
    pos.y += velY * moveSpeed * dt;

    velX = 0;
    velY = 0;

    // move the collider as well
    collider->upperBound.x = pos.x - (colliderW / 2);
    collider->upperBound.y = pos.y - (colliderH / 2) - (enemyH / 2);
    collider->lowerBound.x = pos.x + (colliderW / 2);
    collider->lowerBound.y = pos.y + (colliderH / 2) - (enemyH / 2);

    updateAI(dt);
}
