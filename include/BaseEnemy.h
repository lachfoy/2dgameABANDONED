#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class UiManager;
class ProjectileManager;
class EnemyManager;
class Player;

class BaseEnemy : public BaseDamageable
{
public:
    BaseEnemy(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player);
    virtual ~BaseEnemy() {} // derived enemies can add functionality to their destructors

    int getDamage() const { return damage; }
    
    virtual void updateAI(float dt) = 0; // derived enemies can add any AI functionality if they wish , and it will be called as part of the update function
    
    void update(float dt) override;

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_DAMAGE = 10,
        DEFAULT_MOVE_SPEED = 200
    };

protected:
    int velX = 0; // normalized x velocity
    int velY = 0; // normalized y velocity
    EnemyManager* enemyManager;
    Player* player;
    int enemyW = DEFAULT_W;
    int enemyH = DEFAULT_H;
    float moveSpeed = (float)DEFAULT_MOVE_SPEED;
    int damage = DEFAULT_DAMAGE;
};

#endif