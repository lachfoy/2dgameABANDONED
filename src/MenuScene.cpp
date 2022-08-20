#include "MenuScene.h"

#include "UiManager.h"

#define DEBUG_DRAW 0

MenuScene::MenuScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    ui_manager_ = std::make_shared<UiManager>(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);
    ui_manager_->addTextObject(m_windowWidth / 2, m_windowHeight / 2 - 100, "Menu");
    ui_manager_->addButton(m_windowWidth / 2, m_windowHeight / 2 + 40, "Play");
}

MenuScene::~MenuScene()
{
}

void MenuScene::update(float dt)
{
}

void MenuScene::render(SDL_Renderer* renderer)
{
    // draw a backgrounb
    ui_manager_->renderUiObjects(renderer);
}





