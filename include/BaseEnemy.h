#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

class UIManager;
class ProjectileManager;
class EnemyManager;

class BaseEnemy : public BaseDamageable
{
public:
    BaseEnemy(float x, float y, UIManager* _UIManager, ProjectileManager* projectileManager, EnemyManager* enemyManager);
    virtual ~BaseEnemy(); // derived enemies can add functionality

    int getDamage() const { return damage; }
    
    virtual void updateAI(float dt) = 0; // derived enemies can add any AI functionality if they wish 
    
    void update(float dt) override;
    void render(SDL_Renderer* renderer) = 0;

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
    int enemyW = DEFAULT_W;
    int enemyH = DEFAULT_H;
    float moveSpeed = (float)DEFAULT_MOVE_SPEED;
    int damage = DEFAULT_DAMAGE;
};

#endif