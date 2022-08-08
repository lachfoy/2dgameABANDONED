#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "BaseUiObject.h"

class TextObject : public BaseUiObject
{
public:
    inline TextObject(int x, int y, std::string string, TTF_Font* font);
    inline ~TextObject()
    {
        SDL_DestroyTexture(texture);
    }

    inline void updateString(std::string string);
    inline void updatePosition(const int& newX, const int& newY);

    inline void update(float dt) override;
    inline void render(SDL_Renderer* renderer) override;

private:
    std::string string;
    SDL_Texture* texture;
    SDL_Rect text_rect;

    // does NOT own
    TTF_Font* font;

};

TextObject::TextObject(int x, int y, std::string string, TTF_Font* font)
{
    this->x = x;
    this->y = y;

    this->string = string;

    this->font = font;
}

void TextObject::updatePosition(const int& newX, const int& newY)
{
    this->x = newX;
    this->y = newY;
}

void TextObject::update(float dt)
{
}

void TextObject::render(SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, string.c_str(), SDL_Color{255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_rect.x = x;
    text_rect.y = y;
    text_rect.w = surface->w;
    text_rect.h = surface->h;

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
}

#endif