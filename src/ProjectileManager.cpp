#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"

ProjectileManager::~ProjectileManager()
{
    // delete all the pointers and clear the projectiles vector
    for (int i = 0; i < projectiles.size(); i++) delete projectiles[i];
    projectiles.clear();
}

void ProjectileManager::addFireball(float x, float y, int velX, int velY)
{
    projectiles.push_back(new Fireball(x, y, velX, velY));
}

void ProjectileManager::addFireballExplosion(float x, float y)
{
    projectiles.push_back(new FireballExplosion(x, y));
}

void ProjectileManager::updateProjectiles(float dt)
{
    // update all the projectiles
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->update(dt);
        if (projectiles[i]->removeable)
        {
            projectiles[i]->onDestroy(*this);
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