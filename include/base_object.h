#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include <string>

#include <SDL2/SDL.h>

#include "Vec2f.h"

class BaseObject
{
public:
    inline BaseObject(float x, float y) { pos_.x = x; pos_.y = y; }
    inline BaseObject(const Vec2f& pos) : pos_(pos) {}
    inline ~BaseObject();

    std::string const& name() const { return name_; }
    Vec2f const& pos() const { return pos_; }
    bool removable() const { return removable_; }

    void set_removable(bool removable) { removable_ = removable; }
    
    // debug
    inline void RenderOrigin(SDL_Renderer* renderer);

protected:
    std::string name_ = ""; // use for debug purposes
    Vec2f pos_;
    bool removable_ = false;

};

BaseObject::~BaseObject()
{
    printf("deleting %s\n", name_.c_str()); removable_ = true;
}

void BaseObject::RenderOrigin(SDL_Renderer* renderer)
{
    // draw the origin position
    const int debugPointSize = 4;
    const SDL_Rect rect = { (int)pos_.x - (debugPointSize / 2), (int)pos_.y - (debugPointSize / 2), debugPointSize, debugPointSize };
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // #ebd517 yellow
    SDL_RenderFillRect(renderer, &rect);
}

#endif