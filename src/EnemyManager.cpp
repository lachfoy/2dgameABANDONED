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
    for (const auto& enemy : enemies) delete enemy;
    enemies.clear();
}

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::resolvePlayerProjectileCollisions(const std::vector<BaseProjectile*>& playerProjectiles)
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
                if (projectile->removeOnCollision) projectile->removeable = true;
                printf("%s hit %i enemies\n", projectile->name.c_str(), enemiesHit);
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
    int i = 0;
    for (const auto& enemy : enemies)
    {
        enemy->updateBurning(dt);
        enemy->updateImmuneTimer(dt);
        enemy->updateAI(dt);
        enemy->updatePosition(dt);
        
        if (enemy->removeable)
        {
            delete enemy;
            enemies.erase(enemies.begin() + i); // delete if remove flag is set
        }

        i++;
    }
}

void EnemyManager::renderEnemies(SDL_Renderer* renderer)
{
    // render enemies
    for (const auto& enemy : enemies)
    {
        enemy->render(renderer);
    }
}