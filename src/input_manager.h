#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <SDL2/SDL.h>

class InputManager
{
public:
    InputManager() { keyState = SDL_GetKeyboardState(NULL); }

    void update();

    bool quitRequested() const { return quit; }

    bool keyDown(int key) const { return keysDown[key]; }
    bool keyUp(int key) const { return keysUp[key]; }
    bool keyPressed(SDL_Scancode key) const;


    int getMouseX() const { return mouseX; }
    int getMouseY() const { return mouseY; }
    bool isMouseDown(int mButton) const { return mouseDown[mButton]; }
    bool isMouseUp(int mButton) const { return mouseUp[mButton]; }
    bool mousePressed(int mButton) const;

private:
    bool quit = false;

    const Uint8* keyState = NULL;
    static const int KEYBOARD_SIZE = 104;
    bool keysUp[KEYBOARD_SIZE];
    bool keysDown[KEYBOARD_SIZE];

    Uint32 mouse;
    int mouseX;
    int mouseY;
    static const int MOUSE_SIZE = 2;
    bool mouseUp[MOUSE_SIZE];
    bool mouseDown[MOUSE_SIZE];

};

#endif
