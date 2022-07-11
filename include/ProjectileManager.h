#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseProjectile;
class BaseDamageable;

class ProjectileManager
{
public:
    ProjectileManager() {}
    ~ProjectileManager();

    // Getter for the projectiles vector
    // Needed so other classes can check collisions and such
    inline std::vector<BaseProjectile*> getProjectiles() const { return projectiles; }

    // Adding different kinds of projectiles
    // -------------------------------------
    // Could be replaced by a template function when I understand how that works
    // For example, addProjectile<Fireball>()?
    // -------------------------------------
    inline void addProjectile(BaseProjectile* projectile) { projectiles.push_back(projectile); } // depracated? dont use this anymore
    void addFireball(float x, float y, int velX, int velY);
    void addFireballExplosion(float x, float y);
    void addSword(float x, float y, float offsetX, float offsetY, BaseDamageable* wielder);

    void updateProjectiles(float dt);
    void renderProjectiles(SDL_Renderer* renderer);

private:
    std::vector<BaseProjectile*> projectiles;

};

#endif