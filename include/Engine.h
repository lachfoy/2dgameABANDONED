#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>

#include <SDL2/SDL.h>

class BitmapFont;

class Engine
{
public:
    Engine();

    bool init(int width, int height); // build the window and renderer
    void cleanup(); // deallocate window and renderer
    void run(); // start game loop

protected:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    BitmapFont* bitmapFont;
    
    virtual void onCreate() = 0;
    virtual void onCleanup() = 0;
    virtual void onUpdate(float dt) = 0;
    virtual void onRender() = 0;
};

#endif
