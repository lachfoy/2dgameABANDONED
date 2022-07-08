#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseUiObject;

class UiManager
{
public:
    UiManager() {};
    ~UiManager();

    std::vector<BaseUiObject*> getUiObjects() const { return uiObjects; }
    
    void addUiObject(BaseUiObject* uiObject) { uiObjects.push_back(uiObject); }

    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
};

#endif