#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "Sword.h"
#include "BaseDamageable.h"
#include "SwordSlash.h"
#include "ResourceManager.h"

ProjectileManager::ProjectileManager(ResourceManager* resourceManager, ParticleManager* particleManager)
{
    this->resourceManager = resourceManager; // ptr to resource manager, used when creating projectiles to give them the appropriate textures
    this->particleManager = particleManager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors and delete the pointers
    // enemy projectiles
    for (const auto& projectile : enemyProjectiles) delete projectile;
    enemyProjectiles.clear();

    // player projectiles
    for (const auto& projectile : playerProjectiles) delete projectile;
    playerProjectiles.clear();
}

void ProjectileManager::addFireball(float x, float y, float velX, float velY)
{
    playerProjectiles.push_back(new Fireball(x, y, velX, velY, resourceManager->getTexture("FireballTexture"), particleManager));
}

void ProjectileManager::addFireballExplosion(float x, float y)
{
    playerProjectiles.push_back(new FireballExplosion(x, y, resourceManager->getTexture("FireballExplosionTexture")));
}

void ProjectileManager::addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new Sword(x, y, offsetX, offsetY, resourceManager->getTexture("SwordTexture"), wielder));
}

void ProjectileManager::addSwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new SwordSlash(x, y, offsetX, offsetY, resourceManager->getTexture("SwordSlashTexture"), wielder));
}

void ProjectileManager::updateProjectiles(float dt)
{
    // enemy projectiles
    for (const auto& projectile : enemyProjectiles)
    {
        projectile->updatePosition(dt);
        projectile->updateLifetime(dt);
    }

    // player projectiles
    for (const auto& projectile : playerProjectiles)
    {
        projectile->updatePosition(dt);
        projectile->updateLifetime(dt);
    }
}

void ProjectileManager::removeUnusedProjectiles()
{
    // enemy projectiles
    for (int i = 0; i < enemyProjectiles.size(); i++)
    {
        if (enemyProjectiles[i]->removable)
        {
            enemyProjectiles[i]->destroy(*this);
            delete enemyProjectiles[i];
            enemyProjectiles.erase(enemyProjectiles.begin() + i);
            i--;
        }
    }

    // player projectiles
    for (int i = 0; i < playerProjectiles.size(); i++)
    {
        if (playerProjectiles[i]->removable)
        {
            playerProjectiles[i]->destroy(*this);
            delete playerProjectiles[i];
            playerProjectiles.erase(playerProjectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : enemyProjectiles)
    {
        projectile->render(renderer);
    }

    // player projectiles
    for (const auto& projectile : playerProjectiles)
    {
        projectile->render(renderer);
    }
}

void ProjectileManager::renderDebug(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : enemyProjectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }

    // player projectiles
    for (const auto& projectile : playerProjectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }
}