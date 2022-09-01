#include "enemy_manager.h"

#include "base_enemy.h"
#include "base_projectile.h"
#include "skeleton.h"
#include "UiManager.h"
#include "player.h"
#include "projectile_manager.h"
#include "resource_manager.h"
#include "particle_manager.h"

EnemyManager::EnemyManager(ResourceManagerPtr resource_manager,
    ParticleEmitterManagerPtr particle_emitter_manager,
    UiManagerPtr ui_manager,
    ProjectileManagerPtr projectile_manager,
    PlayerPtr player)
{
    resource_manager_ = resource_manager;
    particle_emitter_manager_ = particle_emitter_manager;
    ui_manager_ = ui_manager;
    projectile_manager_ = projectile_manager;
    player_ = player;
}

EnemyManager::~EnemyManager()
{
    // delete all the pointers and clear the enemies vector
    enemies_.clear();
}

void EnemyManager::AddSkeleton(const Vec2f& pos)
{
    enemies_.push_back(std::make_unique<Skeleton>(pos, resource_manager_, particle_emitter_manager_, *ui_manager_, projectile_manager_, player_));
}

// tests collision against a list of projectiles and deals appropriate damage
void EnemyManager::ResolvePlayerProjectileCollisions(const std::vector<std::unique_ptr<BaseProjectile>>& playerProjectiles)
{
    for (const auto& projectile : playerProjectiles)
    {
        if (!projectile->hasDealtDamage) // if projectile hasnt dealt damage yet, test collisions against all enemies
        {
            // loop through enemies and deal appropriate damage
            int enemiesHit = 0;
            for (const auto& enemy : enemies_)
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

void EnemyManager::UpdateEnemies(float dt)
{
    // update all the enemies
    for (const auto& enemy : enemies_)
    {
        enemy->Update(dt);
    }

    for (int i = 0; i < enemies_.size(); i++)
    {
        if (enemies_[i]->removable())
        {
            //enemies_[i]->OnDestroy(*this);
            enemies_.erase(enemies_.begin() + i);
            i--;
        }
    }
}

void EnemyManager::RenderEnemies(SDL_Renderer* renderer)
{
    // render enemies
    for (const auto& enemy : enemies_)
    {
        enemy->Render(renderer);
    }
}

void EnemyManager::RenderDebug(SDL_Renderer* renderer)
{
    for (const auto& enemy : enemies_)
    {
        enemy->RenderDebug(renderer);
    }
}