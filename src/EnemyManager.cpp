#include "EnemyManager.h"

#include "base_enemy.h"
#include "base_projectile.h"
#include "skeleton.h"
#include "UiManager.h"
#include "player.h"
#include "projectile_manager.h"
#include "resource_manager.h"
#include "particle_manager.h"

EnemyManager::EnemyManager(std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
    std::shared_ptr<UiManager> uiManager,
    std::shared_ptr<ProjectileManager> projectileManager,
    std::shared_ptr<Player> player)
{
    resource_manager_ = resourceManager;
    particle_emitter_manager_ = particle_emitter_manager;
    this->ui_manager_ = uiManager;
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
    m_enemies.push_back(std::make_unique<Skeleton>(pos, resource_manager_, particle_emitter_manager_, *ui_manager_, projectileManager, player));
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
                //if (AABB2i::testOverlap(&projectile->collider_rect(), &enemy->collider_rect()))
                if (SDL_HasIntersection(&projectile->collider_rect(), &enemy->collider_rect()))
                {
                    enemy->TakeDamage(projectile->damage());// make the enemy take damage

                    // also push the enemy away
                    enemy->Push(Vec2f::getDirection(projectile->pos(), enemy->pos()), 100.0f);
                    
                    enemiesHit++;
                }
            }

            // deal with projectile according to flags
            if (projectile->onlyDamageOnce && (enemiesHit > 0))
            {
                projectile->hasDealtDamage = true;
                if (projectile->removeOnCollision) projectile->set_removable(true); // set removable
                printf("%s hit %i enemies\n", projectile->name().c_str(), enemiesHit);
            }
        }
    }
}

void EnemyManager::updateEnemies(float dt)
{
    // update all the enemies
    for (const auto& enemy : m_enemies)
    {
        enemy->Update(dt);
    }
}


void EnemyManager::removeUnusedEnemies()
{
    for (int i = 0; i < m_enemies.size(); i++)
    {
        if (m_enemies[i]->removable())
        {
            //enemies[i]->destroy(*this);
            m_enemies.erase(m_enemies.begin() + i);
            i--;
        }
    }
}

void EnemyManager::RenderEnemies(SDL_Renderer* renderer)
{
    // render enemies
    for (const auto& enemy : m_enemies)
    {
        enemy->Render(renderer);
    }
}

void EnemyManager::RenderDebug(SDL_Renderer* renderer)
{
    for (const auto& enemy : m_enemies)
    {
        enemy->RenderDebug(renderer);
    }
}