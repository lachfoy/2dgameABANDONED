#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>
#include <algorithm>
#include <memory>

#include <SDL2/SDL.h>

#include "BaseProjectile.h"
#include "Vec2f.h"

class BaseDamageable;
class ResourceManager;
class ParticleManager;

class ProjectileManager
{
public:
    ProjectileManager(std::shared_ptr<ResourceManager> resourceManager, ParticleManager* particleManager);
    ~ProjectileManager();

    // Getter for the projectiles vectors
    // Needed so other classes can check collisions and such
    std::vector<std::unique_ptr<BaseProjectile>> const& getPlayerProjectiles() const { return m_playerProjectiles; }
    std::vector<std::unique_ptr<BaseProjectile>> const& getEnemyProjectiles() const { return m_enemyProjectiles; }

    // Adding different kinds of projectiles
    // -------------------------------------
    // Could be replaced by a template function when I understand how that works
    // For example, addProjectile<Fireball>()?
    // -------------------------------------
    //inline void addProjectile(BaseProjectile* projectile) { projectiles.push_back(projectile); } // depracated? dont use this anymore
    void addFireball(const Vec2f& pos, const Vec2f& dir);
    void addFireballExplosion(const Vec2f& pos);
    void addSword(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder);
    void addSwordSlash(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder);

    void updateProjectiles(float dt);
    void resolveProjectileVsEnemyCollisions(const std::vector<BaseDamageable*>& enemies);
    void removeUnusedProjectiles();
    void renderProjectiles(SDL_Renderer* renderer);
    void renderDebug(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<BaseProjectile>> m_playerProjectiles;
    std::vector<std::unique_ptr<BaseProjectile>> m_enemyProjectiles;

    std::shared_ptr<ResourceManager> m_resourceManager;
    ParticleManager* particleManager;

};

#endif