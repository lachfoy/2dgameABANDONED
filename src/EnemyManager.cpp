#include "EnemyManager.h"

#include "BaseEnemy.h"
#include "BaseProjectile.h"
#include "Skeleton.h"
#include "UIManager.h"
#include "Player.h"

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::resolveProjectileCollisions(const std::vector<BaseProjectile*>& projectiles)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < projectiles.size(); j++)
        {
            if (AABB::testOverlap(enemies[i]->getCollider(), projectiles[j]->getCollider()))
            {
                enemies[i]->doDamage(projectiles[j]->getDamage());
                projectiles[j]->removeable = true;
            }
        }
    }
}

// void EnemyManager::addSkeleton(Player* player, UIManager& _UIManager, float x, float y)
// {
//     //enemies.push_back(new Skeleton(x, y, player, _UIManager, ));
// }

void EnemyManager::updateEnemies(float dt)
{
    // update all the enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->update(dt);
        if (enemies[i]->removeable)
        {
            delete enemies[i];
            enemies.erase(enemies.begin() + i); // delete if remove flag is set
        }
    }
}

void EnemyManager::renderEnemies(SDL_Renderer* renderer)
{
    // update all the enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(renderer);
    }
}