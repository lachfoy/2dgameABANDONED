
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL2/SDL.h>

#include "GameScene.h"
#include "PauseScene.h"

class SceneManager
{
public:
    //SceneManager() {}
    //~SceneManager() {}

    enum Scene { // should be private
        GAME,
        PAUSED,
        MENU
    };

    inline Scene getScene() const { return m_currentScene; } // dont use probably lol
    void setScene(const Scene& scene) { m_currentScene = scene; } // also dont use probably
    
    inline bool getPaused() const { return (m_currentScene == PAUSED); }
    inline bool inMenu() const { return (m_currentScene == MENU); }

    void togglePaused()
    {
        if (m_currentScene == GAME)
            m_currentScene = PAUSED;
        else if (m_currentScene == PAUSED)
            m_currentScene = GAME;
    }

    void startGame()
    {
        m_currentScene = GAME;
    }

    void renderCurrentScene();

private:
    Scene m_currentScene;

};

#endif