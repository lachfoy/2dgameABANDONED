#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class Projectile;
class Enemy;

class ProjectileManager
{
public:
    ProjectileManager() {};
    ~ProjectileManager() { projectiles.clear(); }

    void addProjectile(Projectile* projectile) { projectiles.push_back(projectile); }
    inline void resolveEnemyCollisions(Enemy* enemy);

    inline void updateProjectiles(float dt);
    inline void renderProjectiles(SDL_Renderer* renderer);

private:
    std::vector<Projectile*> projectiles;
};

#include "Projectile.h"
#include "Enemy.h"

// tests collision against enemy and deals appropriate damage
void ProjectileManager::resolveEnemyCollisions(Enemy* enemy)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        if (AABB::testOverlap(*projectiles[i]->collider, *enemy->collider))
        {
            enemy->doDamage(projectiles[i]->damage);
            projectiles[i]->removeable = true;
        }
    }
}

void ProjectileManager::updateProjectiles(float dt)
{
    // update all the projectiles
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->update(dt);
        if (projectiles[i]->removeable)
        {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i); // delete if remove flag is set
            
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    // update all the projectiles
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->render(renderer);
    }
}

#endif