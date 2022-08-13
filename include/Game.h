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
    ResourceManager* resourceManager;
    
    GameStateManager* m_gameStateManager;

    void onCreate();
    void onDestroy(); // deallocate window and renderer

};

#endif
