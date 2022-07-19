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

void EnemyManager::addSkeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager)
{
    enemies.push_back(new Skeleton(x, y, uiManager, projectileManager, player));
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
                    enemy->takeDamage(projectile->getDamage());// make the enemy take damage

                    // also push the enemy away
                    int pushVelX = ((enemy->posX - projectile->posX) > 0.0f) ? 1 : -1;
                    int pushVelY = ((enemy->posY - projectile->posY) > 0.0f) ? 1 : -1;
                    enemy->push(pushVelX, pushVelY, -100.0f);
                    
                    enemiesHit++;
                }
            }

            // deal with projectile according to flags
            if (projectile->onlyDamageOnce && (enemiesHit > 0))
            {
                projectile->hasDealtDamage = true;
                if (projectile->removeOnCollision) projectile->removable = true; // set removable
                printf("%s hit %i enemies\n", projectile->name.c_str(), enemiesHit);
            }
        }
    }
}

void EnemyManager::updateEnemies(float dt)
{
    // update all the enemies
    for (const auto& enemy : enemies)
    {
        enemy->updatePush(dt);
        enemy->updateBurning(dt);
        enemy->updateImmuneTimer(dt);
        enemy->updateAI(dt);
        enemy->updatePosition(dt);
    }
}


void EnemyManager::removeUnusedEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i]->removable)
        {
            //enemies[i]->destroy(*this);
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            i--;
        }
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