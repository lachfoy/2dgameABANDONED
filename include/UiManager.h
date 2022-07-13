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

    std::vector<BaseUiObject*> getUiObjects() const { return uiObjects; }
    
    //void addUiObject(BaseUiObject* uiObject) { uiObjects.push_back(uiObject); } // dont use this
    void addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable);
    void addDynamicHealthbar(int length, int height, BaseDamageable* damageable);

    void updateUiObjects(float dt);
    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
};

#endif