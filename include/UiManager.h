#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

#include "InputManager.h"

class BaseUiObject;
class Healthbar;
class DynamicHealthbar;
class BaseDamageable;
class Crosshair;

class UiManager
{
public:
    UiManager(InputManager* inputManager) { this->inputManager = inputManager; }
    ~UiManager();

    std::vector<BaseUiObject*> const& getUiObjects() const { return uiObjects; }
    
    void addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable);
    void addDynamicHealthbar(int length, int height, BaseDamageable* damageable);
    void addCrosshair(int x, int y, int w, int h);

    void updateUiObjects(float dt);
    void removeUnusedUiObjects();
    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
    InputManager* inputManager;
    
};

#endif