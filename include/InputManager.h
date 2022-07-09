#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>

class InputManager
{
public:
    InputManager() {}

    void update();

    bool quitRequested() const { return quit; }

    bool keyDown(int key) const { return keysDown[key]; }
    bool keyUp(int key) const { return keysUp[key]; }
    bool keyPressed(SDL_Scancode key) const;

private:
    const Uint8* keyState = NULL;

    static const int KEYBOARD_SIZE = 282;
    bool quit = false;
    bool keysUp[KEYBOARD_SIZE];
    bool keysDown[KEYBOARD_SIZE];
};

#endif
