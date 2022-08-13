#ifndef BACKGROUNDFILL_H
#define BACKGROUNDFILL_H

#include <SDL2/SDL.h>

#include "BaseUiObject.h"

class BackgroundFill : public BaseUiObject
{
public:
    inline BackgroundFill(SDL_Color color, int windowWidth, int windowHeight);

    inline void update(float dt) override {}
    inline void render(SDL_Renderer* renderer) override;

protected:
    SDL_Color m_color;
    SDL_Rect m_rect;

};

BackgroundFill::BackgroundFill(SDL_Color color, int windowWidth, int windowHeight)
{
    this->x = 0;
    this->y = 0;

    m_color = color;

    m_rect.x = this->x;
    m_rect.y = this->y;
    m_rect.w = windowWidth;
    m_rect.h = windowHeight;
}

void BackgroundFill::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);
}

#endif