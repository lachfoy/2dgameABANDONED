#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "Sword.h"
#include "BaseDamageable.h"
#include "SwordSlash.h"

ProjectileManager::~ProjectileManager()
{
    // // delete all the pointers and clear the projectiles vector
    // for (int i = 0; i < projectiles.size(); i++) delete projectiles[i];
    // projectiles.clear();

    // delete all the pointers and clear the projectiles vector
    for (int i = 0; i < enemyProjectiles.size(); i++) delete enemyProjectiles[i];
    enemyProjectiles.clear();

    // delete all the pointers and clear the projectiles vector
    for (int i = 0; i < playerProjectiles.size(); i++) delete playerProjectiles[i];
    playerProjectiles.clear();
}

void ProjectileManager::addFireball(float x, float y, int velX, int velY)
{
    playerProjectiles.push_back(new Fireball(x, y, velX, velY, this));
}

void ProjectileManager::addFireballExplosion(float x, float y)
{
    playerProjectiles.push_back(new FireballExplosion(x, y));
}

void ProjectileManager::addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new Sword(x, y, offsetX, offsetY, this, wielder));
}

void ProjectileManager::addSwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new SwordSlash(x, y, offsetX, offsetY, wielder));
}

void ProjectileManager::updateProjectiles(float dt)
{
    // update all the projectiles
    for (int i = 0; i < enemyProjectiles.size(); i++)
    {
        enemyProjectiles[i]->updatePosition(dt);
        enemyProjectiles[i]->updateLifetime(dt);
        if (enemyProjectiles[i]->removeable)
        {
            delete enemyProjectiles[i];
            enemyProjectiles.erase(enemyProjectiles.begin() + i); // delete if remove flag is set
        }
    }

    for (int i = 0; i < playerProjectiles.size(); i++)
    {
        playerProjectiles[i]->updatePosition(dt);
        playerProjectiles[i]->updateLifetime(dt);
        if (playerProjectiles[i]->removeable)
        {
            delete playerProjectiles[i];
            playerProjectiles.erase(playerProjectiles.begin() + i); // delete if remove flag is set
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    // render all the projectiles
    for (int i = 0; i < enemyProjectiles.size(); i++)
    {
        enemyProjectiles[i]->render(renderer);
    }

    // render the player projectiles in front
    for (int i = 0; i < playerProjectiles.size(); i++)
    {
        playerProjectiles[i]->render(renderer);
    }
}