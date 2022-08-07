#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h>

class BitmapFont;
class InputManager;
class ResourceManager;
class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;
class ParticleManager;

class Game
{
public:
    Game();

    bool init(int w, int h); // build the window and renderer
    void run(); // start game loop

private:
    int windowWidth;
    int windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    BitmapFont* bitmapFont;
    InputManager* inputManager;
    ResourceManager* resourceManager;
    Player* player;
    ProjectileManager* projectileManager;
    EnemyManager* enemyManager;
    UiManager* uiManager;
    ParticleManager* particleManager;

    void onCreate();
    void onDestroy(); // deallocate window and renderer
    void onUpdate(float dt);
    void onRender();

};

#endif
