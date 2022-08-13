#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "BaseScene.h"

class UiManager;

class MenuScene : public BaseScene
{
public:
    MenuScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight);
    ~MenuScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    UiManager* m_uiManager;

};

#endif