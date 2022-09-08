#include "resource_bar.h"

ResourceBar::ResourceBar(int x, int y, int aWidth, int aHeight, SDL_Texture* aTexture)
{
    this->x = x;
    this->x = y;

    mBgRect.x = x;
    mBgRect.y = y;
    mBgRect.w = aWidth;
    mBgRect.h = aHeight;

    mResourceRect.x = x;
    mResourceRect.y = y;
    mResourceRect.w = aWidth;
    mResourceRect.h = aHeight;

    mTexture = aTexture;
}

void ResourceBar::SetSize(int length, int height)
{
    mBgRect.w = length;
    mBgRect.h = height;

    mResourceRect.w = length;
    mResourceRect.h = height;
}

void ResourceBar::UpdateResource(int aCurrentValue, int aMaxValue)
{
    // calculate the new width of the resource rect as a fraction of the current to max resource, multiplied by the total width (the bgrect width)
    mNewWidth = int((float(aCurrentValue) / aMaxValue) * mBgRect.w);
}

void ResourceBar::Update(float dt)
{
    UpdatePosition();


    // lerp the actual width to the new width over time
    if (mNewWidth != mResourceRect.w) {
        mResourceRect.w = mResourceRect.w + (mNewWidth - mResourceRect.w) * dt; // lerp(a, b, t) = a + (b - a) * t
    }

}

void ResourceBar::Render(SDL_Renderer* renderer)
{
    // draw the bg
    SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff); // dark grey
    SDL_RenderFillRect(renderer, &mBgRect);

    // draw the actual health bar over the bg
    SDL_SetRenderDrawColor(renderer, 0xd1, 0x15, 0x15, 0xff); // #d11515 darkish red
    SDL_RenderFillRect(renderer, &mResourceRect);
}