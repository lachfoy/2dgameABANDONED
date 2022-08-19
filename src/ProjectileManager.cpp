#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "BaseActor.h"
#include "ResourceManager.h"

ProjectileManager::ProjectileManager(std::shared_ptr<ResourceManager> resourceManager, std::shared_ptr<ParticleManager> particleManager)
{
    resource_manager_ = resourceManager;
    particle_manager_ = particleManager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors
    _enemy_projectiles.clear();
    _player_projectiles.clear();
}

void ProjectileManager::addFireball(const Vec2f& pos, const Vec2f& dir)
{
    _player_projectiles.push_back(std::make_unique<Fireball>(pos, dir, resource_manager_, particle_manager_));
}

void ProjectileManager::addFireballExplosion(const Vec2f& pos)
{
    _player_projectiles.push_back(std::make_unique<FireballExplosion>(pos, resource_manager_, particle_manager_));
}

void ProjectileManager::updateProjectiles(float dt)
{
    // enemy projectiles
    for (const auto& projectile : _enemy_projectiles)
    {
        projectile->updatePosition(dt);
        projectile->updateLifetime(dt);
    }

    // player projectiles
    for (const auto& projectile : _player_projectiles)
    {
        projectile->updatePosition(dt);
        projectile->updateLifetime(dt);
    }
}

void ProjectileManager::removeUnusedProjectiles()
{
    // enemy projectiles
    for (int i = 0; i < _enemy_projectiles.size(); i++)
    {
        if (_enemy_projectiles[i]->removable)
        {
            _enemy_projectiles[i]->destroy(*this);
            _enemy_projectiles.erase(_enemy_projectiles.begin() + i);
            i--;
        }
    }

    // player projectiles
    for (int i = 0; i < _player_projectiles.size(); i++)
    {
        if (_player_projectiles[i]->removable)
        {
            _player_projectiles[i]->destroy(*this);
            _player_projectiles.erase(_player_projectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    for (const auto& projectile : _enemy_projectiles) projectile->render(renderer);
    for (const auto& projectile : _player_projectiles) projectile->render(renderer);
}

void ProjectileManager::renderDebug(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : _enemy_projectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }

    // player projectiles
    for (const auto& projectile : _player_projectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }
}