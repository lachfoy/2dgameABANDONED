#include "EnemyManager.h"

#include "BaseEnemy.h"
#include "BaseProjectile.h"
#include "Skeleton.h"
#include "UiManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "ResourceManager.h"
#include "ParticleManager.h"

EnemyManager::EnemyManager(std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager,
    std::shared_ptr<UiManager> uiManager,
    std::shared_ptr<ProjectileManager> projectileManager,
    std::shared_ptr<Player> player)
{
    this->m_resourceManager = resourceManager;
    this->particleManager = particleManager;
    this->m_uiManager = uiManager;
    this->projectileManager = projectileManager;
    this->player = player;
}

EnemyManager::~EnemyManager()
{
    // delete all the pointers and clear the enemies vector
    m_enemies.clear();
}

void EnemyManager::addSkeleton(const Vec2f& pos)
{
    m_enemies.push_back(std::make_unique<Skeleton>(pos, m_resourceManager, particleManager, m_uiManager, projectileManager, player));
}

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::resolvePlayerProjectileCollisions(const std::vector<std::unique_ptr<BaseProjectile>>& playerProjectiles)
{
    for (const auto& projectile : playerProjectiles)
    {
        if (!projectile->hasDealtDamage) // if projectile hasnt dealt damage yet, test collisions against all enemies
        {
            // loop through enemies and deal appropriate damage
            int enemiesHit = 0;
            for (const auto& enemy : m_enemies)
            {
                if (AABB2i::testOverlap(projectile->getCollider(), enemy->getCollider()))
                {
                    enemy->takeDamage(projectile->getDamage());// make the enemy take damage

                    // also push the enemy away
                    enemy->push(Vec2f::getDirection(projectile->pos, enemy->pos), 100.0f);
                    
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
    for (const auto& enemy : m_enemies)
    {
        enemy->update(dt);
    }
}


void EnemyManager::removeUnusedEnemies()
{
    for (int i = 0; i < m_enemies.size(); i++)
    {
        if (m_enemies[i]->removable)
        {
            //enemies[i]->destroy(*this);
            m_enemies.erase(m_enemies.begin() + i);
            i--;
        }
    }
}

void EnemyManager::renderEnemies(SDL_Renderer* renderer)
{
    // render enemies
    for (const auto& enemy : m_enemies)
    {
        enemy->renderShadow(renderer);
    }
    for (const auto& enemy : m_enemies)
    {
        enemy->render(renderer);
    }
}

void EnemyManager::renderDebug(SDL_Renderer* renderer)
{
    for (const auto& enemy : m_enemies)
    {
        enemy->renderCollider(renderer);
        enemy->renderOrigin(renderer);
    }
}