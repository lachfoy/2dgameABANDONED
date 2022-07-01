#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <string>

#include <SDL2/SDL.h>

class BitmapFont
{
public:
    inline BitmapFont(SDL_Renderer* renderer, const char* path);
    inline ~BitmapFont();

    inline void renderText(SDL_Renderer* renderer, int x, int y, std::string text);

private:
    SDL_Texture* bitmapFontTexture;
    SDL_Rect chars[128];
};

BitmapFont::BitmapFont(SDL_Renderer* renderer, const char* path)
{
    // load texture as surface
    SDL_Surface* bitmapFontSurface = SDL_LoadBMP(path);
    if (!bitmapFontSurface)
    {
        printf("BitmapFont::Failed to load surface: %s\n", SDL_GetError());
    }

    // save texture and free temp surface
    bitmapFontTexture = SDL_CreateTextureFromSurface(renderer, bitmapFontSurface);
    SDL_FreeSurface(bitmapFontSurface);

    // each glyph is 8x16 pixels
    int cellW = 8;
    int cellH = 16;

    // the charset is 128 by 128 pixels, or 16 by 8 8x16 pixel glpyhs
    int currentChar = 0;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 16; ++col)
        {
            chars[currentChar].x = cellW * col;
            chars[currentChar].y = cellH * row;
            chars[currentChar].w = cellW;
            chars[currentChar].h = cellH;

            ++currentChar;
        }
    }
}

BitmapFont::~BitmapFont()
{
    SDL_DestroyTexture(bitmapFontTexture);
}

void BitmapFont::renderText(SDL_Renderer* renderer, int x, int y, std::string text)
{
    if (bitmapFontTexture)
    {
        int curX = x;
        int curY = y;
        for (int i = 0; i < text.length(); ++i)
        {
            if (text[i] == ' ') curX += 8;
            else if (text[i] == '\n')
            {
                curY += 28; // move down and reset x
                curX = x;
            }
            else
            {
                int ascii = (unsigned char)(text[i] - 32);

                SDL_Rect rect;
                rect.x = curX;
                rect.y = curY;
                rect.w = 8;
                rect.h = 16;

                SDL_RenderCopy(renderer, bitmapFontTexture, &chars[ascii], &rect);

                curX += 8;
            }
            
        }

    }
}

#endif