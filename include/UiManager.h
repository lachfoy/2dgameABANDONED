#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseUiObject;

class UiManager
{
public:
    UiManager() {};
    ~UiManager() { uiObjects.clear(); }

    std::vector<BaseUiObject*> getUiObjects() const { return uiObjects; }
    void addUiObject(BaseUiObject* uiObject) { uiObjects.push_back(uiObject); }

    inline void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
};

#include "BaseUiObject.h"

void UiManager::renderUiObjects(SDL_Renderer* renderer)
{
    // update all the UiObjects
    for (int i = 0; i < uiObjects.size(); i++)
    {
        uiObjects[i]->render(renderer);
    }
}

#endif