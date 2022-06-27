#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "AABB.h"

class Player
{
public:
    Player();

    float posX;
    float posY;
    AABB* collider;

    void handleInput(SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    int playerW;
    int playerH;
    int velX;
    int velY;
    float moveSpeed;
};

#endif