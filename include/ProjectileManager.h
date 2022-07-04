#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseProjectile;
class BaseEnemy;

class ProjectileManager
{
public:
    ProjectileManager() {};
    ~ProjectileManager() { projectiles.clear(); }

    std::vector<BaseProjectile*> getProjectiles() const { return projectiles; }
    void addProjectile(BaseProjectile* projectile) { projectiles.push_back(projectile); }

    inline void updateProjectiles(float dt);
    inline void renderProjectiles(SDL_Renderer* renderer);

private:
    std::vector<BaseProjectile*> projectiles;
};

#include "BaseProjectile.h"
#include "BaseEnemy.h"

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