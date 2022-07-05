#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseEnemy;
class BaseProjectile;
class Player;
class UIManager;

class EnemyManager
{
public:
    EnemyManager() {};
    ~EnemyManager() { enemies.clear(); }

    std::vector<BaseEnemy*> getEnemies() const { return enemies; }
    
    void addEnemy(BaseEnemy* enemy) { enemies.push_back(enemy); } // deprecated -- don't use this anymore
    void addSkeleton(Player* player, UIManager& _UIManager, float x, float y);

    void resolveProjectileCollisions(const std::vector<BaseProjectile*>& projectiles);

    void updateEnemies(float dt);
    void renderEnemies(SDL_Renderer* renderer);

private:
    std::vector<BaseEnemy*> enemies;
};

#endif