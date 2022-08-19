#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "BaseUiObject.h"

class Button : public BaseUiObject
{
public:
    inline Button(int x, int y, std::string text, TTF_Font* font);
    inline ~Button();

    //inline void updateString(std::string string); // these should be added as a derived class
    //inline void updatePosition(const int& newX, const int& newY); // these should be added as a derived class

    inline void update(float dt) override; // these should be added as a derived class
    inline void render(SDL_Renderer* renderer) override;

protected:
    std::string text;
    SDL_Texture* texture;
    SDL_Rect text_rect;
    SDL_Rect bg_rect;
    const int paddingX = 16;
    const int paddingY = 8;
    const SDL_Color button_colorNormal = {128, 128, 128, 255};
    const SDL_Color button_colorHover = {200, 200, 200, 255};
    SDL_Color button_color;

    // does NOT own
    TTF_Font* font;

};

Button::Button(int x, int y, std::string text, TTF_Font* font)
{
    this->x = x;
    this->y = y;

    this->text = text;

    this->font = font;

    button_color = button_colorNormal;
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
}

// void Button::updatePosition(const int& newX, const int& newY)
// {
//     this->x = newX;
//     this->y = newY;
// }

void checkMouseIntersection()
{
    
}

void Button::update(float dt)
{
}

void Button::render(SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color{255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_rect.x = x - (int)(surface->w / 2);
    text_rect.y = y - (int)(surface->h / 2);
    text_rect.w = surface->w;
    text_rect.h = surface->h;
    SDL_FreeSurface(surface);

    bg_rect.x = text_rect.x - paddingX;
    bg_rect.y = text_rect.y - paddingY;
    bg_rect.w = text_rect.w + (paddingX * 2);
    bg_rect.h = text_rect.h + (paddingY * 2);

    SDL_SetRenderDrawColor(renderer, button_color.r, button_color.g, button_color.b, button_color.a);
    SDL_RenderFillRect(renderer, &bg_rect);
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
}

#endif