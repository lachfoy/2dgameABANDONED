#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class InputManager;
class ResourceManager;
class SceneManager;

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

    std::shared_ptr<InputManager> m_inputManager;
    std::shared_ptr<ResourceManager> m_resourceManager;
    std::shared_ptr<SceneManager> m_sceneManager;

    void create();
    void destroy(); // deallocate window and renderer

};

#endif
