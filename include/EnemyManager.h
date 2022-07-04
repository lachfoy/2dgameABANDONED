#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseEnemy;
class BaseProjectile;

class EnemyManager
{
public:
    EnemyManager() {};
    ~EnemyManager() { enemies.clear(); }

    std::vector<BaseEnemy*> getEnemies() const { return enemies; }
    void addEnemy(BaseEnemy* enemy) { enemies.push_back(enemy); }

    inline void resolveProjectileCollisions(const std::vector<BaseProjectile*>& projectiles);

    inline void updateEnemies(float dt);
    inline void renderEnemies(SDL_Renderer* renderer);

private:
    std::vector<BaseEnemy*> enemies;
};

#include "BaseEnemy.h"
#include "BaseProjectile.h"

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

#endif