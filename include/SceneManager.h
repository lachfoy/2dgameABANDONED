#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL2/SDL.h>

#include "BaseScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "MenuScene.h"

//#include <map> // could use a map function to more easily iterate through different scenes

class InputManager;
class ResourceManager;

class SceneManager
{
public:
    SceneManager(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~SceneManager();

    inline bool getPaused() const { return (m_currentScene == m_pauseScene); }
    inline bool inMenu() const { return (m_currentScene == m_menuScene); }

    void startMenu();
    void startGame();
    void togglePaused();

    void updateCurrentScene(float dt);
    void renderCurrentScene(SDL_Renderer* renderer);

private:
    BaseScene* m_currentScene = nullptr;
    GameScene* m_gameScene = nullptr;
    PauseScene* m_pauseScene = nullptr;
    MenuScene* m_menuScene = nullptr;

    // not owned
    std::shared_ptr<InputManager> m_inputManager;
    std::shared_ptr<ResourceManager> m_resourceManager;
    int m_windowWidth;
    int m_windowHeight;

};

#endif