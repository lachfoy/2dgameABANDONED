#ifndef PAUSE_SCENE_H_
#define PAUSE_SCENE_H_

#include "BaseScene.h"

class UiManager;

class PauseScene : public BaseScene
{
public:
    PauseScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~PauseScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<UiManager> m_uiManager;

};

#endif