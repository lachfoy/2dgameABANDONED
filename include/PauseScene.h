#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "BaseScene.h"

class UiManager;

class PauseScene : public BaseScene
{
public:
    PauseScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight);
    ~PauseScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    UiManager* m_uiManager;

};

#endif