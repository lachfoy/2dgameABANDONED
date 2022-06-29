#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "BaseObject.h"
#include "AABB.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

class Game : public Engine
{
public:
    Game();

private:
    Player* player;
    AABB* test_collider;

    std::vector<Projectile*> projectiles;
    std::vector<Enemy*> enemies;

    void onCreate();
    void onCleanup();
    void handleInput(SDL_Event& e);
    void onUpdate(float dt);
    void onRender();
};

#endif
