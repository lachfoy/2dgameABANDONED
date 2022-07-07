#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>

#include "Engine.h"

class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;

class Game : public Engine
{
public:
    Game();

private:
    Player* player;
    ProjectileManager* projectileManager;
    EnemyManager* enemyManager;
    UiManager* uiManager;

    void onCreate();
    void onCleanup();
    void onUpdate(float dt);
    void onRender();
};

#endif
