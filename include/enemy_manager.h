#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>

#include <SDL2/SDL.h>

#include "Vec2f.h"

class ResourceManager;
class ParticleEmitterManager;
class UiManager;
class ProjectileManager;
class Player;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;
typedef std::shared_ptr<UiManager> UiManagerPtr;
typedef std::shared_ptr<ProjectileManager> ProjectileManagerPtr;
typedef std::shared_ptr<Player> PlayerPtr;

class BaseEnemy;
class BaseProjectile;
class Skeleton;

class EnemyManager
{
public:
    EnemyManager(ResourceManagerPtr resourceManager,
        ParticleEmitterManagerPtr particle_emitter_manager,
        UiManagerPtr uiManager,
        ProjectileManagerPtr projectileManager,
        PlayerPtr player);

    ~EnemyManager();

    std::vector<std::unique_ptr<BaseEnemy>> const& enemies() const { return enemies_; }
    
    void AddSkeleton(const Vec2f& pos);

    void ResolvePlayerProjectileCollisions(const std::vector<std::unique_ptr<BaseProjectile>>& player_projectiles);

    void UpdateEnemies(float dt);
    void CleanUpUnusedEnemies();
    void RenderEnemies(SDL_Renderer* renderer);
    void RenderDebug(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<BaseEnemy>> enemies_;

    ResourceManagerPtr resource_manager_;
    ParticleEmitterManagerPtr particle_emitter_manager_;
    UiManagerPtr ui_manager_;
    ProjectileManagerPtr projectile_manager_;
    PlayerPtr player_;
    
};

#endif