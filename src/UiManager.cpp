#include "UiManager.h"

#include "BaseUiObject.h"
#include "Healthbar.h"
#include "DynamicHealthbar.h"

UiManager::~UiManager()
{
    // delete all the pointers and clear the uiObjects vector
    for (const auto& uiObject : uiObjects) delete uiObject;
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
    // render UiObjects
    for (const auto& uiObject : uiObjects)
    {
        uiObject->render(renderer);
    }
}

void UiManager::updateUiObjects(float dt)
{
    // update uiObjects
    int i = 0;
    for (const auto& uiObject : uiObjects)
    {
        uiObject->update(dt);
        if (uiObject->removeable)
        {
            delete uiObject;
            uiObjects.erase(uiObjects.begin() + i); // delete if remove flag is set
        }
        i++;
    }
}