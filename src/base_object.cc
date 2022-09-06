#include "base_object.h"

BaseObject::BaseObject(float x, float y)
{
    pos_.x = x;
    pos_.y = y;
}

BaseObject::BaseObject(const Vec2f& pos)
{
    pos_ = pos;
}

void BaseObject::RenderOrigin(SDL_Renderer* renderer)
{
    // draw the origin position
    const int debugPointSize = 4;
    const SDL_Rect rect = { (int)pos_.x - (debugPointSize / 2), (int)pos_.y - (debugPointSize / 2), debugPointSize, debugPointSize };
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &rect);
}