#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

class BaseUIObject;

class UIManager
{
public:
    UIManager() {};
    ~UIManager() { UIObjects.clear(); }

    std::vector<BaseUIObject*> getUIObjects() const { return UIObjects; }
    void addUIObject(BaseUIObject* UIObject) { UIObjects.push_back(UIObject); }

    inline void renderUIObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUIObject*> UIObjects;
};

#include "BaseUIObject.h"

void UIManager::renderUIObjects(SDL_Renderer* renderer)
{
    // update all the UIObjects
    for (int i = 0; i < UIObjects.size(); i++)
    {
        UIObjects[i]->render(renderer);
    }
}

#endif