#ifndef RESOURCE_BAR_H_
#define RESOURCE_BAR_H_

#include <SDL2/SDL.h>

#include "BaseUiObject.h"

class BaseCharacter;

// Use mozzilla naming style
class ResourceBar : public BaseUiObject
{
public:
    ResourceBar(int x, int y, int aWidth, int aHeight, SDL_Texture* aTexture, BaseCharacter* aCharacter);

    // update the healthbar internal length and height as well as the rects
    void SetSize(int length, int height);

    void UpdateResource(int aCurrentValue, int aMaxValue); // take a current health and a max health and update the UI rects
    virtual void UpdatePosition() {} // this can be overridden by the moving healthbar variant

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

protected:
    SDL_Texture* mTexture;
    BaseCharacter* mCharacter;
    SDL_Rect mBgRect;
    SDL_Rect mResourceRect;
    int mNewWidth; // width when updated

};

#endif