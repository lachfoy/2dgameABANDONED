#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

#include "BaseProjectile.h"

class BaseDamageable;

class ProjectileManager
{
public:
    ProjectileManager() {}
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
    void addFireball(float x, float y, int velX, int velY);
    void addFireballExplosion(float x, float y);
    void addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);
    void addSwordSlash(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);

    void updateProjectiles(float dt);
    void removeUnusedProjectiles();
    void renderProjectiles(SDL_Renderer* renderer);

private:
    //std::vector<BaseProjectile*> projectiles;
    std::vector<BaseProjectile*> playerProjectiles;
    std::vector<BaseProjectile*> enemyProjectiles;

};

#endif