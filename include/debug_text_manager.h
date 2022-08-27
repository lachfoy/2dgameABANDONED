#ifndef DEBUG_TEXT_MANAGER_H_
#define DEBUG_TEXT_MANAGER_H_

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"

class DebugTextManager
{
public:
    inline DebugTextManager(TTF_Font* font)
    {
        font_ = font;
    }

    inline ~DebugTextManager()
    {
        SDL_DestroyTexture(texture_);
        debug_strings_.clear();
    }

    inline void Update(const Player& player)
    {
        debug_strings_ = player.getDebugInfo();
    }

    inline void Render(SDL_Renderer* renderer)
    {
        int x = 10;
        int y = 10;
        int vertical_offset = 30;
        for (const auto& string : debug_strings_)
        {
            RenderString(renderer, string, x, y);
            y += vertical_offset;
        }
    }

private:
    std::vector<std::string> debug_strings_;

    SDL_Texture* texture_;

    // does NOT own
    TTF_Font* font_;

    inline void RenderString(SDL_Renderer* renderer, std::string text, int x, int y)
    {
        SDL_Surface* surface = TTF_RenderText_Blended(font_, text.c_str(), SDL_Color{255, 255, 255});
        texture_ = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect text_rect { x, y, surface->w, surface->h };
        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer, texture_, NULL, &text_rect);
    }

};

#endif
