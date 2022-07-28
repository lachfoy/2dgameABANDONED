#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

#include "BaseProjectile.h"

class BaseDamageable;
class ResourceManager;
class ParticleManager;

class ProjectileManager
{
public:
    ProjectileManager(ResourceManager* resourceManager, ParticleManager* particleManager)
    {
        this->resourceManager = resourceManager; // ptr to resource manager, used when creating projectiles to give them the appropriate textures
        this->particleManager = particleManager;
    }

    ~ProjectileManager();

    // Getter for the projectiles vector
    // Needed so other classes can check collisions and such
    //inline std::vector<BaseProjectile*> getProjectiles() const { return projectiles; }
    std::vector<BaseProjectile*> const& getPlayerProjectiles() const { return playerProjectiles; }
    std::vector<BaseProjectile*> const& getEnemyProjectiles() const { return enemyProjectiles; }

    // Adding different kinds of projectiles
    // -------------------------------------
    // Could be replaced by a template function when I understand how that works
    // For example, addProjectile<Fireball>()?
    // -------------------------------------
    //inline void addProjectile(BaseProjectile* projectile) { projectiles.push_back(projectile); } // depracated? dont use this anymore
    void addFireball(float x, float y, float velX, float velY);
    void addFireballExplosion(float x, float y);
    void addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);
    void addSwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);

    void updateProjectiles(float dt);
    void resolveProjectileVsEnemyCollisions(const std::vector<BaseDamageable*>& enemies);
    void removeUnusedProjectiles();
    void renderProjectiles(SDL_Renderer* renderer);
    void renderDebug(SDL_Renderer* renderer);

private:
    //std::vector<BaseProjectile*> projectiles;
    std::vector<BaseProjectile*> playerProjectiles;
    std::vector<BaseProjectile*> enemyProjectiles;

    ResourceManager* resourceManager;
    ParticleManager* particleManager;

};

#endif