#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

#include "BaseEnemy.h"

class Skeleton : public BaseEnemy
{
public:
    Skeleton(float x, float y);
    ~Skeleton() {}

    void updateAI(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    float AiTime;
    float AiTimer;

};

#endif