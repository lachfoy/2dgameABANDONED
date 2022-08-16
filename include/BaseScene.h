#ifndef BASESCENE_H
#define BASESCENE_H

#include <memory>

#include <SDL2/SDL.h>

class InputManager;
class ResourceManager;

class BaseScene
{
public:
    BaseScene(InputManager* inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);

    virtual void update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

protected:
    InputManager* m_inputManager;
    std::shared_ptr<ResourceManager> m_resourceManager;
    int m_windowWidth;
    int m_windowHeight;

};

#endif