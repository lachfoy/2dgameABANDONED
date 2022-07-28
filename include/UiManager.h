#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

#include "InputManager.h"
#include "ResourceManager.h"

class BaseUiObject;
class Healthbar;
class DynamicHealthbar;
class BaseDamageable;
class Crosshair;

class UiManager
{
public:
    UiManager(InputManager* inputManager, ResourceManager* resourceManager)
    {
        this->inputManager = inputManager;
        this->resourceManager = resourceManager;
    }
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
    ResourceManager* resourceManager;
    
};

#endif