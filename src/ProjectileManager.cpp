#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "Sword.h"
#include "BaseDamageable.h"
#include "SwordSlash.h"

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

void ProjectileManager::addFireball(float x, float y, int velX, int velY)
{
    playerProjectiles.push_back(new Fireball(x, y, velX, velY));
}

void ProjectileManager::addFireballExplosion(float x, float y)
{
    playerProjectiles.push_back(new FireballExplosion(x, y));
}

void ProjectileManager::addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new Sword(x, y, offsetX, offsetY, wielder));
}

void ProjectileManager::addSwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder)
{
    playerProjectiles.push_back(new SwordSlash(x, y, offsetX, offsetY, wielder));
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

// tests collision against a list of projectiles and deals appropriate damage
void ProjectileManager::resolveProjectileVsEnemyCollisions(const std::vector<BaseDamageable*>& enemies)
{
    for (const auto& projectile : playerProjectiles)
    {
        if (!projectile->hasDealtDamage) // if projectile hasnt dealt damage yet, test collisions against all enemies
        {
            // loop through enemies and deal appropriate damage
            int enemiesHit = 0;
            for (const auto& enemy : enemies)
            {
                if (AABB::testOverlap(projectile->getCollider(), enemy->getCollider()))
                {
                    enemy->takeDamage(projectile->getDamage());
                    enemiesHit++;
                }
            }

            // deal with projectile according to flags
            if (projectile->onlyDamageOnce && (enemiesHit > 0))
            {
                projectile->hasDealtDamage = true;
                if (projectile->removeOnCollision) projectile->removable; // set removable
                printf("%s hit %i enemies\n", projectile->name.c_str(), enemiesHit);
            }
        }
    }
}

void ProjectileManager::removeUnusedProjectiles()
{
    // this actually works im like 90% sure holy shit
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