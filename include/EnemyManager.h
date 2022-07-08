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
    ~EnemyManager() { enemies.clear(); }

    std::vector<BaseEnemy*> getEnemies() const { return enemies; }
    
    void addEnemy(BaseEnemy* enemy) { enemies.push_back(enemy); } // deprecated -- don't use this anymore
    void addSkeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager);

    void resolveProjectileCollisions(const std::vector<BaseProjectile*>& projectiles);

    void updateEnemies(float dt);
    void renderEnemies(SDL_Renderer* renderer);

private:
    Player* player; // pointer to player
    std::vector<BaseEnemy*> enemies;
};

#endif