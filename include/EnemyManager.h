#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseEnemy;
class BaseProjectile;
class Player;
class UiManager;
class Skeleton;
class ProjectileManager;
class ResourceManager;
class ParticleManager;

class EnemyManager
{
public:
    EnemyManager(ResourceManager* resourceManager, ParticleManager* particleManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player);
    ~EnemyManager();

    std::vector<BaseEnemy*> const& getEnemies() const { return enemies; }
    
    void addSkeleton(float x, float y);

    void resolvePlayerProjectileCollisions(const std::vector<BaseProjectile*>& playerProjectiles);

    void updateEnemies(float dt);
    void removeUnusedEnemies();
    void renderEnemies(SDL_Renderer* renderer);
    void renderDebug(SDL_Renderer* renderer);

private:
    ResourceManager* m_resourceManager; // pointer to resource manager
    ParticleManager* particleManager;
    UiManager* m_uiManager; // pointer to ui manager
    ProjectileManager* projectileManager; // pointer to projectile manager
    Player* player; // pointer to player
    std::vector<BaseEnemy*> enemies;
    
};

#endif