#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>

#include "Engine.h"

class Player;
class AABB;
class EnemyManager;
class ProjectileManager;
class HealthBar;

class Game : public Engine
{
public:
    Game();

private:
    Player* player;
    AABB* test_collider;
    HealthBar* playerHealthBar;

    ProjectileManager* projectileManager;
    EnemyManager* enemyManager;

    void onCreate();
    void onCleanup();
    void handleInput(SDL_Event& e);
    void onUpdate(float dt);
    void onRender();
};

#endif
