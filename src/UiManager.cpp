#include "UiManager.h"

#include "BaseUiObject.h"

UiManager::~UiManager()
{
    // delete all the pointers and clear the uiObjects vector
    for (int i = 0; i < uiObjects.size(); i++) delete uiObjects[i];
    uiObjects.clear();
}

void UiManager::renderUiObjects(SDL_Renderer* renderer)
{
    // update all the UiObjects
    for (int i = 0; i < uiObjects.size(); i++)
    {
        uiObjects[i]->render(renderer);
    }
}