#include "BaseScene.h"

#include "InputManager.h"
#include "resource_manager.h"

BaseScene::BaseScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    resource_manager_ = resourceManager;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}