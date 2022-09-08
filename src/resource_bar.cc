#include "resource_bar.h"

ResourceBar::ResourceBar(int x, int y, int aWidth, int aHeight, SDL_Texture* aTexture, SDL_Texture* aBgTexture)
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
    mBgTexture = aBgTexture;
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
        mResourceRect.w = mNewWidth + int((mResourceRect.w - mNewWidth) * dt); // lerp(a, b, t) = a + (b - a) * t
    }

}

void ResourceBar::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, mBgTexture, NULL, &mBgRect);
    SDL_RenderCopy(renderer, mTexture, NULL, &mResourceRect);
}