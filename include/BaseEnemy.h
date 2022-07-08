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
    
    // derived enemies can add any AI functionality if they wish
    virtual void updateAI(float dt) = 0;
    void updateHealthBarPosition();

protected:
    EnemyManager* enemyManager;
    Player* player;
    int damage;
};

#endif