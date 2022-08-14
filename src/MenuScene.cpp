#include "MenuScene.h"

#include "UiManager.h"

#define DEBUG_DRAW 0

MenuScene::MenuScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    m_uiManager = new UiManager(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
    m_uiManager->addBackgroundFill({0x74, 0x74, 0x74, 0x74});
    m_uiManager->addTextObject(m_windowWidth / 2 - 60, m_windowHeight / 2 - 200, "Menu");
}

MenuScene::~MenuScene()
{
    delete m_uiManager;
}

void MenuScene::update(float dt)
{
}

void MenuScene::render(SDL_Renderer* renderer)
{
    m_uiManager->renderUiObjects(renderer);
}





