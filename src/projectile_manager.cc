#include "projectile_manager.h"

#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "fireball.h"
#include "fireball_explosion.h"
#include "base_character.h"

ProjectileManager::ProjectileManager(ResourceManagerPtr resource_manager, ParticleEmitterManagerPtr particle_emitter_manager)
{
    resource_manager_ = resource_manager;
    particle_emitter_manager_ = particle_emitter_manager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors
    enemy_projectiles_.clear();
    player_projectiles_.clear();
}

void ProjectileManager::AddFireball(const Vec2f& pos, const Vec2f& dir)
{
    std::unique_ptr<BaseProjectile> projectile = std::make_unique<Fireball>(
        pos,
        dir,
        resource_manager_->GetTexture("fireball_texture"),
        resource_manager_,
        particle_emitter_manager_
    );
    projectile->OnCreate(*this);
    Mix_PlayChannel(-1, resource_manager_->GetSound("fireball_sound"), 0);
    player_projectiles_.push_back(std::move(projectile));
}

void ProjectileManager::AddFireballExplosion(const Vec2f& pos)
{
    std::unique_ptr<BaseProjectile> projectile = std::make_unique<FireballExplosion>(
        pos,
        resource_manager_->GetTexture("fireball_texture"),
        resource_manager_,
        particle_emitter_manager_
    );
    projectile->OnCreate(*this);
    Mix_PlayChannel(-1, resource_manager_->GetSound("fireball_explosion_sound"), 0);
    player_projectiles_.push_back(std::move(projectile));
}

void ProjectileManager::UpdateProjectiles(float dt)
{
    // update projectiles
    for (const auto& projectile : enemy_projectiles_) projectile->Update(dt);
    for (const auto& projectile : player_projectiles_) projectile->Update(dt);
}

void ProjectileManager::CleanUpUnusedProjectiles()
{
    // remove unused projectiles
    for (int i = 0; i < enemy_projectiles_.size(); i++)
    {
        if (enemy_projectiles_[i]->removable())
        {
            enemy_projectiles_[i]->OnDestroy(*this);
            enemy_projectiles_.erase(enemy_projectiles_.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < player_projectiles_.size(); i++)
    {
        if (player_projectiles_[i]->removable())
        {
            player_projectiles_[i]->OnDestroy(*this);
        }
    }

    player_projectiles_.erase(
        std::remove_if(
            player_projectiles_.begin(),
            player_projectiles_.end(),
            [](auto const& projectile) {
                return projectile->removable();
            }
        ),
        player_projectiles_.end()
    );
}


void ProjectileManager::RenderProjectiles(SDL_Renderer* renderer)
{
    for (const auto& projectile : enemy_projectiles_) projectile->Render(renderer);
    for (const auto& projectile : player_projectiles_) projectile->Render(renderer);
}

void ProjectileManager::RenderDebug(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : enemy_projectiles_)
    {
        projectile->RenderDebug(renderer);
    }

    // player projectiles
    for (const auto& projectile : player_projectiles_)
    {
        projectile->RenderDebug(renderer);
    }
}