#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <cmath>

#include <SDL2/SDL.h>

#include "base_object.h"
#include "vec2f.h"

class Particle : public BaseObject
{
public:
    Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, float gravity, int size, float lifetime, const SDL_Color& color, SDL_Texture* texture);
    ~Particle() {}

    inline Vec2f const& dir() const { return dir_; }

    void Update(float dt);
    void Render(SDL_Renderer* renderer);

private:
    Vec2f dir_;
    float movespeed_;
    float gravity_;
    int start_size_;
    int size_;
    float start_lifetime_;
    float current_lifetime_;
    Uint8 alpha_;
    SDL_Color color_;
    SDL_Rect rect_;
    SDL_Texture* texture_; // texture to use for rendering, particle does not have ownership

};

#endif