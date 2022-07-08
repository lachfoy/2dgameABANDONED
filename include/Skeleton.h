#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(float x, float y, UiManager* uiManager, ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player);
    ~Skeleton() override {}

    void updateAI(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    bool thinking;
    float thinkingTime;
    float thinkingTimer;
};

#endif