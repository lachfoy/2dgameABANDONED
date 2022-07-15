#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseUiObject;
class Healthbar;
class DynamicHealthbar;
class BaseDamageable;

class UiManager
{
public:
    UiManager() {};
    ~UiManager();

    std::vector<BaseUiObject*> const& getUiObjects() const { return uiObjects; }
    
    void addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable);
    void addDynamicHealthbar(int length, int height, BaseDamageable* damageable);

    void updateUiObjects(float dt);
    void removeUnusedUiObjects();
    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
    
};

#endif