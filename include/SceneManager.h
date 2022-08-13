
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL2/SDL.h>

#include "BaseScene.h"
#include "GameScene.h"
#include "PauseScene.h"

class InputManager;
class ResourceManager;

class SceneManager
{
public:
    SceneManager(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
    {
        m_gameScene = new GameScene(inputManager, resourceManager, windowWidth, windowHeight);
        m_gameScene->create();
        m_pauseScene = new PauseScene(inputManager, resourceManager, windowWidth, windowHeight);
        m_pauseScene->create();
    }

    ~SceneManager()
    {
        // BUG: causes seg fault
        m_currentScene->destroy();
        m_gameScene->destroy();
        m_pauseScene->destroy();
        m_menuScene->destroy();

        delete m_currentScene;
        delete m_gameScene;
        delete m_pauseScene;
        delete m_menuScene;
    }

    // enum Scene { // should be private
    //     GAME,
    //     PAUSED,
    //     MENU
    // };

    //inline Scene getScene() const { return m_currentScene; } // dont use probably lol
    //void setScene(const Scene& scene) { m_currentScene = scene; } // also dont use probably
    
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
        // if (m_currentScene == GAME)
        //     m_currentScene = PAUSED;
        // else if (m_currentScene == PAUSED)
        //     m_currentScene = GAME;

        if (m_currentScene == m_gameScene)
            m_currentScene = m_pauseScene;
        else if (m_currentScene == m_pauseScene)
            m_currentScene = m_gameScene;
    }

    inline void startMenu()
    {
        printf("Starting Menu\n");
        if (!m_menuScene) { m_menuScene->create(); printf("Loading Menu Scene\n"); }
        m_currentScene = m_menuScene;
    }

    inline void startGame()
    {
        //m_currentScene = GAME;
        printf("Starting Game\n");
        if (!m_gameScene) { m_gameScene->create(); printf("Loading Game Scene\n"); }
        m_currentScene = m_gameScene;
    }

    inline void updateCurrentScene(float dt)
    {
        m_currentScene->update(dt);
    }

    inline void renderCurrentScene(SDL_Renderer* renderer)
    {
        // switch (m_currentScene)
        // {
        // case GAME:
        // {
        //     m_gameScene.render(renderer);
        //     break;
        // }
        // case PAUSED:
        // {
        //     m_pauseScene.render(renderer);
        //     break;
        // }
        // }
        m_currentScene->render(renderer);
    }

private:
    //Scene m_currentScene;
    BaseScene* m_currentScene = nullptr;
    GameScene* m_gameScene = nullptr;
    PauseScene* m_pauseScene = nullptr;
    BaseScene* m_menuScene = nullptr;

};

#endif