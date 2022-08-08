#include "UiManager.h"

#include "BaseUiObject.h"
#include "Healthbar.h"
#include "DynamicHealthbar.h"
#include "Crosshair.h"
#include "TextObject.h"

UiManager::~UiManager()
{
    // delete all the pointers and clear the uiObjects vector
    for (const auto& uiObject : uiObjects) delete uiObject;
    uiObjects.clear();

    TTF_CloseFont(font);
}

void UiManager::addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable)
{
    uiObjects.push_back(new Healthbar(x, y, length, height, damageable));
}

void UiManager::addDynamicHealthbar(int length, int height, BaseDamageable* damageable)
{
    uiObjects.push_back(new DynamicHealthbar(length, height, damageable));
}

void UiManager::addCrosshair(int x, int y, int w, int h)
{
    uiObjects.push_back(new Crosshair(x, y, w, h, inputManager, resourceManager->getTexture("CrosshairTexture")));
}

void UiManager::addTextObject(int x, int y, std::string text)
{
    uiObjects.push_back(new TextObject(x, y, text, font));
}

void UiManager::updateUiObjects(float dt)
{
    for (const auto& uiObject : uiObjects)
    {
        uiObject->update(dt);
    }
}

void UiManager::removeUnusedUiObjects()
{
    for (int i = 0; i < uiObjects.size(); i++)
    {
        if (uiObjects[i]->removable)
        {
            //uiObjects[i]->destroy(*this);
            delete uiObjects[i];
            uiObjects.erase(uiObjects.begin() + i);
            i--;
        }
    }
}

void UiManager::renderUiObjects(SDL_Renderer* renderer)
{
    // render UiObjects
    for (const auto& uiObject : uiObjects)
    {
        uiObject->render(renderer);
    }
}