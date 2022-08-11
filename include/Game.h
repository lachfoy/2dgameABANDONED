#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class BitmapFont;
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
    Player* player;
    ProjectileManager* projectileManager;
    EnemyManager* enemyManager;
    UiManager* uiManager;
    ParticleManager* particleManager;

    // scene specific
    UiManager* pauseUiManager;
    
    void onCreate();
    void onDestroy(); // deallocate window and renderer
    
    void gameUpdate(float dt);
    void pausedUpdate(float dt);

    void gameRender();
    void pausedRender();
    
};

#endif
