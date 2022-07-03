#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>

#include "Engine.h"

class Player;
class AABB;
class Enemy;
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

    //std::vector<Projectile*> projectiles;
    ProjectileManager* projectileManager;
    std::vector<Enemy*> enemies;

    void onCreate();
    void onCleanup();
    void handleInput(SDL_Event& e);
    void onUpdate(float dt);
    void onRender();
};

#endif
