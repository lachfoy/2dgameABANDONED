
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL2/SDL.h>

#include "BaseScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "MenuScene.h"

#include <map> // could use a map function to more easily iterate through different scenes

class InputManager;
class ResourceManager;

class SceneManager
{
public:
    SceneManager(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
    {
        m_inputManager = inputManager;
        m_resourceManager = resourceManager;
        m_windowWidth = windowWidth;
        m_windowHeight = windowHeight;
    }

    ~SceneManager()
    {
        if (m_gameScene) delete m_gameScene;
        if (m_pauseScene) delete m_pauseScene;
        if (m_menuScene) delete m_pauseScene;
    }
    
    inline bool getPaused() const
    {
        //return (m_currentScene == PAUSED);
        return (m_currentScene == m_pauseScene);
    }

    inline bool inMenu() const
    {
        //return (m_currentScene == MENU);
        return (m_currentScene == m_menuScene);
    }

    inline void togglePaused()
    {
        if (m_currentScene == m_gameScene)
            m_currentScene = m_pauseScene;
        else if (m_currentScene == m_pauseScene)
            m_currentScene = m_gameScene;
    }

    inline void startMenu()
    {
        printf("Starting Menu\n");
        if (!m_menuScene) { m_menuScene = new MenuScene(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight); }
        m_currentScene = m_menuScene;
    }

    inline void startGame()
    {
        printf("Starting Game\n");
        if (!m_gameScene) { m_gameScene = new GameScene(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight); }
        m_currentScene = m_gameScene;
    }

    inline void updateCurrentScene(float dt)
    {
        m_currentScene->update(dt);
    }

    inline void renderCurrentScene(SDL_Renderer* renderer)
    {
        m_currentScene->render(renderer);
    }

private:
    BaseScene* m_currentScene = nullptr;
    GameScene* m_gameScene = nullptr;
    PauseScene* m_pauseScene = nullptr;
    MenuScene* m_menuScene = nullptr;

    // not owned
    InputManager* m_inputManager;
    ResourceManager* m_resourceManager;
    int m_windowWidth;
    int m_windowHeight;

};

#endif