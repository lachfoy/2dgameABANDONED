#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <cmath>

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "Vec2f.h"

class Particle : public BaseObject
{
public:
    Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, SDL_Texture* texture, int size, float lifetime);
    ~Particle() {}

    inline Vec2f const& dir() const { return dir_; }
    
    void Update(float dt);
    void Render(SDL_Renderer* renderer);

private:
    Vec2f dir_;
    float movespeed_;
    SDL_Texture* texture_; // texture to use for rendering, particle does not have ownership
    int size_;
    float start_lifetime_;
    float current_lifetime_;
    Uint8 alpha_;

};

#endif