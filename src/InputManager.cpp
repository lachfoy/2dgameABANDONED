#include "InputManager.h"

void InputManager::update()
{
    for (int i = 0; i < KEYBOARD_SIZE; i++)
    {
        // reset keys
        keysDown[i] = false;
        keysUp[i] = false;
    }

        for (int i = 0; i < MOUSE_SIZE; i++)
    {
        // reset mouse
        mouseDown[i] = false;
        mouseUp[i] = false;
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
            const int index = event.key.keysym.scancode;
            keysDown[index] = true;
        } break;

        case SDL_KEYUP:
        {
            keyState = SDL_GetKeyboardState(NULL);
            const int index = event.key.keysym.scancode;
            keysUp[index] = false;
        } break;

        case SDL_MOUSEMOTION:
        {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        } break;

        case SDL_MOUSEBUTTONUP:
        {
            mouse = SDL_GetMouseState(&mouseX, &mouseY);
            if (event.button.button == SDL_BUTTON_LEFT) mouseUp[0] = true;
            else if (event.button.button == SDL_BUTTON_RIGHT) mouseUp[1] = true;
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
            mouse = SDL_GetMouseState(&mouseX, &mouseY);
            if (event.button.button == SDL_BUTTON_LEFT) mouseDown[0] = true;
            else if (event.button.button == SDL_BUTTON_RIGHT) mouseDown[1] = true;
        } break;

        }
    }
}

bool InputManager::keyPressed(SDL_Scancode key) const
{
    if (keyState[key]) return true;
    return false;
}

bool InputManager::mousePressed(int mButton) const
{
    if (mButton == 0 && mouse & SDL_BUTTON(1)) return true;
    else if (mButton == 1 && mouse & SDL_BUTTON(3)) return true;

    return false;
}

