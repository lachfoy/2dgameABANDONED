#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SDL2/SDL.h>

#include "BaseUiObject.h"

#include "InputManager.h"

class Crosshair : public BaseUiObject
{
public:
    inline Crosshair(int x, int y, int w, int h, std::shared_ptr<InputManager> inputManager, SDL_Texture* texture);

    inline void updatePosition(const int& newX, const int& newY); // update center position
    inline void update(float dt) override;
    inline void render(SDL_Renderer* renderer) override;

private:
    SDL_Rect crosshair_rect;
    std::shared_ptr<InputManager> m_inputManager;
    SDL_Texture* texture;

};

Crosshair::Crosshair(int x, int y, int w, int h, std::shared_ptr<InputManager> inputManager, SDL_Texture* texture)
{
    this->x = x - (int)(w / 2.0f);
    this->y = y - (int)(h / 2.0f);

    crosshair_rect.x = this->x;
    crosshair_rect.y = this->y;
    crosshair_rect.w = w;
    crosshair_rect.h = h;

    this->m_inputManager = inputManager;
    this->texture = texture;
}

void Crosshair::updatePosition(const int& newX, const int& newY)
{
    this->x = newX - (int)(crosshair_rect.w / 2.0f);
    this->y = newY - (int)(crosshair_rect.h / 2.0f);
}

void Crosshair::update(float dt)
{
    updatePosition(m_inputManager->getMouseX(), m_inputManager->getMouseY());

    crosshair_rect.x = this->x;
    crosshair_rect.y = this->y;
}

void Crosshair::render(SDL_Renderer* renderer)
{
    //SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    //SDL_RenderDrawRect(renderer, &crosshair_rect);

    SDL_RenderCopy(renderer, texture, NULL, &crosshair_rect);
}

#endif