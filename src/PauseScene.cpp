#include "PauseScene.h"

#include "UiManager.h"

#define DEBUG_DRAW 0

PauseScene::PauseScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    ui_manager_ = std::make_shared<UiManager>(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);
    ui_manager_->addTextObject(m_windowWidth / 2 - 60, m_windowHeight / 2 - 20, "Paused!");
}

PauseScene::~PauseScene()
{
}

void PauseScene::update(float dt)
{
}

void PauseScene::render(SDL_Renderer* renderer)
{
    // draw a background
    ui_manager_->renderUiObjects(renderer);
}





