#ifndef BASE_TEXT_OBJECT_H_
#define BASE_TEXT_OBJECT_H_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "BaseUiObject.h"

class BaseTextObject : public BaseUiObject
{
public:
    inline BaseTextObject(int x, int y, std::string text, TTF_Font* font);
    inline ~BaseTextObject();

    //inline void updateString(std::string string); // these should be added as a derived class
    //inline void updatePosition(const int& newX, const int& newY); // these should be added as a derived class

    inline void Update(float dt) override; // these should be added as a derived class
    inline void Render(SDL_Renderer* renderer) override;

protected:
    std::string text;
    SDL_Texture* texture;
    SDL_Rect text_rect;

    // does NOT own
    TTF_Font* font;

};

BaseTextObject::BaseTextObject(int x, int y, std::string text, TTF_Font* font)
{
    this->x = x;
    this->y = y;

    this->text = text;

    this->font = font;
}

BaseTextObject::~BaseTextObject()
{
    SDL_DestroyTexture(texture);
}

// void BaseTextObject::updatePosition(const int& newX, const int& newY)
// {
//     this->x = newX;
//     this->y = newY;
// }

void BaseTextObject::Update(float dt)
{
}

void BaseTextObject::Render(SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color{255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_rect.x = x - (int)(surface->w / 2);
    text_rect.y = y - (int)(surface->h / 2);
    text_rect.w = surface->w;
    text_rect.h = surface->h;

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
}

#endif