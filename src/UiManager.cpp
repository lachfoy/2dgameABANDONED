#include "UiManager.h"

#include "BaseUiObject.h"
#include "Healthbar.h"
#include "DynamicHealthbar.h"

UiManager::~UiManager()
{
    // delete all the pointers and clear the uiObjects vector
    for (int i = 0; i < uiObjects.size(); i++) delete uiObjects[i];
    uiObjects.clear();
}

void UiManager::addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable)
{
    uiObjects.push_back(new Healthbar(x, y, length, height, damageable));
}

void UiManager::addDynamicHealthbar(int length, int height, BaseDamageable* damageable)
{
    uiObjects.push_back(new DynamicHealthbar(length, height, damageable));
}

void UiManager::renderUiObjects(SDL_Renderer* renderer)
{
    // update all the UiObjects
    for (int i = 0; i < uiObjects.size(); i++)
    {
        uiObjects[i]->render(renderer);
    }
}

void UiManager::updateUiObjects(float dt)
{
    // update all the uiObjects
    for (int i = 0; i < uiObjects.size(); i++)
    {
        uiObjects[i]->update(dt);
        if (uiObjects[i]->removeable)
        {
            delete uiObjects[i];
            uiObjects.erase(uiObjects.begin() + i); // delete if remove flag is set
        }
    }
}