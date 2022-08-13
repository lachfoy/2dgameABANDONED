#include "BaseScene.h"

#include "InputManager.h"
#include "ResourceManager.h"

BaseScene::BaseScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    m_resourceManager = resourceManager;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}