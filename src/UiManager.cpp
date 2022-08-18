#include "UiManager.h"

#include "InputManager.h"
#include "ResourceManager.h"
#include "BaseUiObject.h"
#include "Healthbar.h"
#include "DynamicHealthbar.h"
#include "Crosshair.h"
#include "BaseTextObject.h"
#include "Button.h"

UiManager::UiManager(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    m_resourceManager = resourceManager;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}

UiManager::~UiManager()
{
    m_uiObjects.clear();
}

void UiManager::addHealthbar(int x, int y, int length, int height, BaseActor* damageable)
{
    m_uiObjects.push_back(std::make_unique<Healthbar>(x, y, length, height, damageable));
}

void UiManager::addDynamicHealthbar(int length, int height, BaseActor* damageable)
{
    m_uiObjects.push_back(std::make_unique<DynamicHealthbar>(length, height, damageable));
}

void UiManager::addCrosshair(int x, int y, int w, int h)
{
    m_uiObjects.push_back(std::make_unique<Crosshair>(x, y, w, h, m_inputManager, m_resourceManager->getTexture("CrosshairTexture")));
}

void UiManager::addTextObject(int x, int y, std::string text)
{
    m_uiObjects.push_back(std::make_unique<BaseTextObject>(x, y, text, m_resourceManager->getFont("ArialHeader")));
}

void UiManager::addButton(int x, int y, std::string text)
{
    m_uiObjects.push_back(std::make_unique<Button>(x, y, text, m_resourceManager->getFont("ArialBody")));
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