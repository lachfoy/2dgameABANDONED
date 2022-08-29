#include "projectile_manager.h"

#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "fireball.h"
#include "fireball_explosion.h"
#include "magic_missile.h"
#include "base_character.h"

ProjectileManager::ProjectileManager(std::shared_ptr<ResourceManager> resource_manager,
    std::shared_ptr<ParticleManager> particle_manager, std::shared_ptr<ParticleEmitterManager> particle_emitter_manager)
{
    resource_manager_ = resource_manager;
    particle_manager_ = particle_manager;
    particle_emitter_manager_ = particle_emitter_manager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors
    _enemy_projectiles.clear();
    _player_projectiles.clear();
}

void ProjectileManager::AddFireball(const Vec2f& pos, const Vec2f& dir)
{
    std::unique_ptr<BaseProjectile> projectile = std::make_unique<Fireball>(pos, dir, resource_manager_, particle_manager_, particle_emitter_manager_);
    projectile->OnCreate(*this);
    Mix_PlayChannel(-1, resource_manager_->GetSound("fireball_sound"), 0);
    _player_projectiles.push_back(std::move(projectile));
}

void ProjectileManager::AddFireballExplosion(const Vec2f& pos)
{
    std::unique_ptr<BaseProjectile> projectile = std::make_unique<FireballExplosion>(pos, resource_manager_, particle_manager_, particle_emitter_manager_);
    projectile->OnCreate(*this);
    Mix_PlayChannel(-1, resource_manager_->GetSound("fireball_explosion_sound"), 0);
    _player_projectiles.push_back(std::move(projectile));
}

void ProjectileManager::AddMagicMissile(const Vec2f& pos, const Vec2f& dir, BaseObject* target)
{
    std::unique_ptr<BaseProjectile> projectile = std::make_unique<MagicMissile>(pos, dir, resource_manager_, particle_manager_, particle_emitter_manager_, target);
    projectile->OnCreate(*this);
    _player_projectiles.push_back(std::move(projectile));
}

void ProjectileManager::UpdateProjectiles(float dt)
{
    // update projectiles
    for (const auto& projectile : _enemy_projectiles) projectile->Update(dt);
    for (const auto& projectile : _player_projectiles) projectile->Update(dt);

    // remove unused projectiles
    for (int i = 0; i < _enemy_projectiles.size(); i++)
    {
        if (_enemy_projectiles[i]->removable())
        {
            _enemy_projectiles[i]->OnDestroy(*this);
            _enemy_projectiles.erase(_enemy_projectiles.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < _player_projectiles.size(); i++)
    {
        if (_player_projectiles[i]->removable())
        {
            _player_projectiles[i]->OnDestroy(*this);
            _player_projectiles.erase(_player_projectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileManager::RenderProjectiles(SDL_Renderer* renderer)
{
    for (const auto& projectile : _enemy_projectiles) projectile->Render(renderer);
    for (const auto& projectile : _player_projectiles) projectile->Render(renderer);
}

void ProjectileManager::renderDebug(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : _enemy_projectiles)
    {
        projectile->RenderDebug(renderer);
    }

    // player projectiles
    for (const auto& projectile : _player_projectiles)
    {
        projectile->RenderDebug(renderer);
    }
}