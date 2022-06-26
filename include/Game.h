#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "Engine.h"
#include "Player.h"

class Game : public Engine
{
public:
    Game();

private:
    Player* player;

    void onCreate();
    void onCleanup();
    void handleInput(SDL_Event& e);
    void onUpdate(float dt);
    void onRender();
};

#endif