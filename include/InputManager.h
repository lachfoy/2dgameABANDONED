#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>



// singleton lol
class InputManager
{
public:
    static InputManager* getInstance();

    void update();

    bool quitRequested() const { return quit; }

    bool keyDown(int key) const { return keysDown[key]; }
    bool keyUp(int key) const { return keysUp[key]; }
    bool keyPressed(SDL_Scancode key) const;

private:
    static InputManager* instance;
    InputManager();
    InputManager(InputManager const&) {};
    void operator=(InputManager const&) {};

    const Uint8* keyState = NULL;

    static const int KEYBOARD_SIZE = 282;
    bool quit = false;
    bool keysUp[KEYBOARD_SIZE];
    bool keysDown[KEYBOARD_SIZE];
};

#endif
