#include "InputManager.h"

InputManager* InputManager::instance = 0;

InputManager::InputManager() {}

InputManager* InputManager::getInstance()
{
    if (instance == 0)
    {
        instance = new InputManager();
    }

    return instance;
}

void InputManager::update()
{
    keyState = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < KEYBOARD_SIZE; i++)
    {
        // reset keys
        keysDown[i] = false;
        keysUp[i] = false;
    }

    // run event loop
    SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

        case SDL_KEYDOWN:
        {
            keyState = SDL_GetKeyboardState(NULL);
            int index = event.key.keysym.scancode;
            keysDown[index] = true;
        } break;

        case SDL_KEYUP:
        {
            keyState = SDL_GetKeyboardState(NULL);
            int index = event.key.keysym.scancode;
            keysUp[index] = false;
        } break;
        }
    }
}

bool InputManager::keyPressed(SDL_Scancode key) const
{
    if (keyState[key]) return true;
    return false;
}