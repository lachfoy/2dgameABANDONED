#include "PauseScene.h"

#include "UiManager.h"

#define DEBUG_DRAW 0

PauseScene::PauseScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{

}

void PauseScene::create()
{
    m_uiManager = new UiManager(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
    m_uiManager->addBackgroundFill({0x74, 0x74, 0x74, 0x74});
    m_uiManager->addTextObject(m_windowWidth / 2 - 60, m_windowHeight / 2 - 20, "Paused!");
    
}

void PauseScene::destroy()
{
    delete m_uiManager;
}

void PauseScene::update(float dt)
{
}

void PauseScene::render(SDL_Renderer* renderer)
{
    m_uiManager->renderUiObjects(renderer);
}




