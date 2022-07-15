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

class EnemyManager
{
public:
    EnemyManager(Player* player);
    ~EnemyManager();

    std::vector<BaseEnemy*> const& getEnemies() const { return enemies; }
    
    void addSkeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager);

    void resolvePlayerProjectileCollisions(const std::vector<BaseProjectile*>& playerProjectiles);

    void updateEnemies(float dt);
    void removeUnusedEnemies();
    void renderEnemies(SDL_Renderer* renderer);

private:
    Player* player; // pointer to player
    std::vector<BaseEnemy*> enemies;
};

#endif