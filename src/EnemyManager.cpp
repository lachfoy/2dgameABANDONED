#include "EnemyManager.h"

#include "BaseEnemy.h"
#include "BaseProjectile.h"
#include "Skeleton.h"
#include "UiManager.h"
#include "Player.h"
#include "ProjectileManager.h"

EnemyManager::EnemyManager(Player* player)
{
    this->player = player;
}

EnemyManager::~EnemyManager()
{
    // delete all the pointers and clear the enemies vector
    for (int i = 0; i < enemies.size(); i++) delete enemies[i];
    enemies.clear();
}

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::resolveProjectileCollisions(const std::vector<BaseProjectile*>& projectiles)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < projectiles.size(); j++)
        {
            if (projectiles[j]->onlyDamageOnce && !projectiles[j]->hasDealtDamage)
            {
                if (AABB::testOverlap(enemies[i]->getCollider(), projectiles[j]->getCollider()))
                {
                    enemies[i]->takeDamage(projectiles[j]->getDamage());
                    projectiles[j]->hasDealtDamage = true;
                    if (projectiles[j]->removeOnCollision) projectiles[j]->removeable = true;
                }
            }
        }
    }
}

void EnemyManager::addSkeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager)
{
    enemies.push_back(new Skeleton(x, y, uiManager, projectileManager, this, player));
}

void EnemyManager::updateEnemies(float dt)
{
    // update all the enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        
        enemies[i]->updateBurning(dt);
        enemies[i]->updateImmuneTimer(dt);
        enemies[i]->updateAI(dt);
        enemies[i]->updatePosition(dt);
        
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