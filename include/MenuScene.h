#ifndef MENU_SCENE_H_
#define MENU_SCENE_H_

#include "BaseScene.h"

class UiManager;

class MenuScene : public BaseScene
{
public:
    MenuScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~MenuScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<UiManager> m_uiManager;

};

#endif