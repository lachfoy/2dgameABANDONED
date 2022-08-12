#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class InputManager;
class ResourceManager;
class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;
class ParticleManager;
class GameStateManager;

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

    InputManager* inputManager;
    GameStateManager* m_gameStateManager;
    ResourceManager* resourceManager;

    // game scene specific
    Player* player;
    ProjectileManager* projectileManager;
    EnemyManager* enemyManager;
    UiManager* uiManager;
    ParticleManager* particleManager;

    // pause scene specific
    UiManager* pauseUiManager;

    // menu scene specific
    UiManager* menuUiManager;
    
    void onCreate();
    void onDestroy(); // deallocate window and renderer
    
    void gameUpdate(float dt);
    void pauseUpdate(float dt);
    void menuUpdate(float dt);

    void gameRender();
    void pauseRender();
    void menuRender();
    
};

#endif
