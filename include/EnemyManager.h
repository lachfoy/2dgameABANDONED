#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "Vec2f.h"

class BaseEnemy;
class BaseProjectile;
class Player;
class UiManager;
class Skeleton;
class ProjectileManager;
class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;

class EnemyManager
{
public:
    EnemyManager(std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
        std::shared_ptr<UiManager> uiManager,
        std::shared_ptr<ProjectileManager> projectileManager,
        std::shared_ptr<Player> player);
    ~EnemyManager();

    std::vector<std::unique_ptr<BaseEnemy>> const& getEnemies() const { return m_enemies; }
    
    void addSkeleton(const Vec2f& pos);

    void resolvePlayerProjectileCollisions(const std::vector<std::unique_ptr<BaseProjectile>>& playerProjectiles);

    void updateEnemies(float dt);
    void removeUnusedEnemies();
    void renderEnemies(SDL_Renderer* renderer);
    void renderDebug(SDL_Renderer* renderer);

private:
    std::shared_ptr<ResourceManager> resource_manager_; // pointer to resource manager
    std::shared_ptr<ParticleManager> particleManager;
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager_;
    std::shared_ptr<UiManager> ui_manager_; // pointer to ui manager
    std::shared_ptr<ProjectileManager> projectileManager; // pointer to projectile manager
    std::shared_ptr<Player> player; // pointer to player
    std::vector<std::unique_ptr<BaseEnemy>> m_enemies;
    
};

#endif