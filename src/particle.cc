#include "particle.h"

#include <iostream>

Particle::Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, float gravity, int size, float lifetime, const SDL_Color& color, SDL_Texture* texture)
    : BaseObject(pos)
{
    name_ = "particle";//debug
    dir_ = dir;
    movespeed_ = movespeed;
    gravity_ = gravity; // -0.4f
    start_size_ = size;
    size_ = start_size_;
    start_lifetime_ = lifetime;
    current_lifetime_ = start_lifetime_;
    color_ = color;
    texture_ = texture;

    SDL_SetTextureColorMod(texture_, color_.r, color_.g, color_.b);
}

void Particle::Update(float dt)
{
    if (current_lifetime_ <= 0.0f)
    {
        removable_ = true;
    }
    else
    {        
        // what percent of X is Y. Use the percentage formula: Y/X = P%
        float lifetime_progress = (current_lifetime_ / start_lifetime_);

        alpha_ = lifetime_progress * 255;
        SDL_SetTextureAlphaMod(texture_, alpha_);

        pos_.x += dir_.x * movespeed_ * dt;
        pos_.y += dir_.y * movespeed_ * dt + gravity_;

        size_ = lifetime_progress * start_size_;

        // update the rect for renderering
        rect_ = { int(pos_.x) - int(size_ / 2), int(pos_.y) - int(size_ / 2), size_, size_ };
        
        current_lifetime_ -= dt;
    }
}

void Particle::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}
