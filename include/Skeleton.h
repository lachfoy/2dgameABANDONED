#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(float x, float y, ResourceManager* resourceManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player);

    void updateAI(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    float targetX;
    float targetY;
    float thinkingTime;
    float thinkingTimer;
    
};

#endif