#include "UiManager.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "BaseUiObject.h"
#include "Healthbar.h"
#include "DynamicHealthbar.h"
#include "Crosshair.h"
#include "BaseTextObject.h"
#include "PlayerDebugText.h"
#include "BackgroundFill.h"

UiManager::UiManager(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    m_resourceManager = resourceManager;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;

    m_font = TTF_OpenFont("../fonts/arial.ttf", 28);
}

UiManager::~UiManager()
{
    // delete all the pointers and clear the uiObjects vector
    for (const auto& uiObject : m_uiObjects) delete uiObject;
    m_uiObjects.clear();

    TTF_CloseFont(m_font);
}

void UiManager::addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable)
{
    m_uiObjects.push_back(new Healthbar(x, y, length, height, damageable));
}

void UiManager::addDynamicHealthbar(int length, int height, BaseDamageable* damageable)
{
    m_uiObjects.push_back(new DynamicHealthbar(length, height, damageable));
}

void UiManager::addCrosshair(int x, int y, int w, int h)
{
    m_uiObjects.push_back(new Crosshair(x, y, w, h, m_inputManager, m_resourceManager->getTexture("CrosshairTexture")));
}

void UiManager::addTextObject(int x, int y, std::string text)
{
    m_uiObjects.push_back(new BaseTextObject(x, y, text, m_font));
}

void UiManager::addPlayerDebugText(int x, int y, Player* player)
{
    m_uiObjects.push_back(new PlayerDebugText(x, y, "", m_font, player));  
}

void UiManager::addBackgroundFill(SDL_Color color)
{
    m_uiObjects.push_back(new BackgroundFill(color, m_windowWidth, m_windowHeight));
}

void UiManager::updateUiObjects(float dt)
{
    for (const auto& uiObject : m_uiObjects)
    {
        uiObject->update(dt);
    }
}

void UiManager::removeUnusedUiObjects()
{
    for (int i = 0; i < m_uiObjects.size(); i++)
    {
        if (m_uiObjects[i]->removable)
        {
            //uiObjects[i]->destroy(*this);
            delete m_uiObjects[i];
            m_uiObjects.erase(m_uiObjects.begin() + i);
            i--;
        }
    }
}

void UiManager::renderUiObjects(SDL_Renderer* renderer)
{
    // render UiObjects
    for (const auto& uiObject : m_uiObjects)
    {
        uiObject->render(renderer);
    }
}