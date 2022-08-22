#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_

#include <vector>
#include <algorithm>
#include <memory>

#include <SDL2/SDL.h>

#include "base_projectile.h"
#include "Vec2f.h"

class BaseActor;
class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;

class ProjectileManager
{
public:
    ProjectileManager(std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager, std::shared_ptr<ParticleEmitterManager> particle_emitter_manager);
    ~ProjectileManager();

    // Getter for the projectiles vectors
    // Needed so other classes can check collisions and such
    std::vector<std::unique_ptr<BaseProjectile>> const& player_projectiles() const { return _player_projectiles; }
    std::vector<std::unique_ptr<BaseProjectile>> const& enemy_projectiles() const { return _enemy_projectiles; }

    // Adding different kinds of projectiles
    // -------------------------------------
    // Could be replaced by a template function when I understand how that works
    // For example, addProjectile<Fireball>()?
    // -------------------------------------
    //inline void addProjectile(BaseProjectile* projectile) { projectiles.push_back(projectile); } // depracated? dont use this anymore
    void AddFireball(const Vec2f& pos, const Vec2f& dir);
    void AddFireballExplosion(const Vec2f& pos);
    void AddMagicMissile(const Vec2f& pos, const Vec2f& dir, BaseObject* target);

    void UpdateProjectiles(float dt);
    void resolveProjectileVsEnemyCollisions(const std::vector<BaseActor*>& enemies);
    void removeUnusedProjectiles();
    void RenderProjectiles(SDL_Renderer* renderer);
    void renderDebug(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<BaseProjectile>> _player_projectiles;
    std::vector<std::unique_ptr<BaseProjectile>> _enemy_projectiles;

    std::shared_ptr<ResourceManager> resource_manager_;
    std::shared_ptr<ParticleManager> particle_manager_;
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager_;

};

#endif