#include "SceneManager.h"

#include "BaseScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "MenuScene.h"

SceneManager::SceneManager(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    resource_manager_ = resourceManager;
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}

SceneManager::~SceneManager()
{
    if (m_gameScene) delete m_gameScene;
    if (m_pauseScene) delete m_pauseScene;
    if (m_menuScene) delete m_menuScene;
}

void SceneManager::startMenu()
{
    printf("Starting Menu\n");
    if (!m_menuScene)
        m_menuScene = new MenuScene(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);
    m_currentScene = m_menuScene;
}

void SceneManager::startGame()
{
    printf("Starting Game\n");
    if (!m_gameScene)
        m_gameScene = new GameScene(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);
    m_currentScene = m_gameScene;
}

void SceneManager::togglePaused()
{
    if (m_currentScene == m_gameScene)
        m_currentScene = m_pauseScene;
    else if (m_currentScene == m_pauseScene)
        m_currentScene = m_gameScene;
}

void SceneManager::updateCurrentScene(float dt)
{
    m_currentScene->update(dt);
}

void SceneManager::renderCurrentScene(SDL_Renderer* renderer)
{
    m_currentScene->render(renderer);
}
