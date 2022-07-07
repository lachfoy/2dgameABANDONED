#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Player;
class HealthBar;
class UIManager;
class EnemyManager;

class Skeleton : public BaseEnemy
{
public:
    Skeleton(Player* player, UIManager& _UIManager, float x, float y);
    ~Skeleton() {}

    void onDestroy(EnemyManager& enemyManager) override;
    void updateAI(float dt) override;

    void render(SDL_Renderer* renderer) override;

private:
    Player* player;
    bool thinking;
    float thinkingTime;
    float thinkingTimer;
};

#endif