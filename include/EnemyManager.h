#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseEnemy;
class Projectile;

class EnemyManager
{
public:
    EnemyManager() {};
    ~EnemyManager() { enemies.clear(); }

    inline void updateEnemies(float dt);
    inline void renderEnemies(SDL_Renderer* renderer);

    inline void resolveProjectileCollisions(const std::vector<Projectile*>& projectiles);

    void addEnemy(BaseEnemy* enemy) { enemies.push_back(enemy); }

private:
    std::vector<BaseEnemy*> enemies;
};

#include "BaseEnemy.h"
#include "Projectile.h"

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::resolveProjectileCollisions(const std::vector<Projectile*>& projectiles)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < projectiles.size(); j++)
        {
            if (AABB::testOverlap(*enemies[i]->collider, *projectiles[j]->collider))
            {
                enemies[i]->doDamage(projectiles[j]->damage);
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