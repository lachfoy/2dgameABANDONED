#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include <string>

#include <SDL2/SDL.h>

#include "vec2f.h"

class BaseObject
{
public:
    BaseObject(float x, float y);
    BaseObject(const Vec2f& pos);

    std::string const& name() const { return name_; }
    Vec2f const& pos() const { return pos_; }
    bool removable() const { return removable_; }

    void set_removable(bool removable) { removable_ = removable; }
    
    // debug
    void RenderOrigin(SDL_Renderer* renderer);

protected:
    std::string name_ = ""; // use for debug purposes
    Vec2f pos_;
    bool removable_ = false;

};

#endif