#include "SceneManager.h"

#include "BaseScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "MenuScene.h"

SceneManager::SceneManager(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
{
    m_inputManager = inputManager;
    m_resourceManager = resourceManager;
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
        m_menuScene = new MenuScene(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
    m_currentScene = m_menuScene;
}

void SceneManager::startGame()
{
    printf("Starting Game\n");
    if (!m_gameScene)
        m_gameScene = new GameScene(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
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