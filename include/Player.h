#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player
{
public:
    Player();

    float posX;
    float posY;

    void handleInput(SDL_Event& e);
    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    SDL_Rect debug_point;
    int width;
    int height;
    int velX;
    int velY;
    float moveSpeed;
};

#endif