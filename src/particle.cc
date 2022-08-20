#include "particle.h"

#include <iostream>

Particle::Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, SDL_Texture* texture, int size, float lifetime)
    : BaseObject(pos)
{
    dir_ = dir;
    movespeed_ = movespeed;
    texture_ = texture;
    size_ = size;
    start_lifetime_ = lifetime;
    current_lifetime_ = start_lifetime_;
}

void Particle::Update(float dt)
{
    if (current_lifetime_ <= 0.0f)
        removable = true;
    else
    {
        // what percent of X is Y. Use the percentage formula: Y/X = P%
        alpha_ = (current_lifetime_ / start_lifetime_) * 255;
        std::cout << std::to_string(alpha_) + "\n";
        pos.x += dir_.x * movespeed_ * dt;
        pos.y += dir_.y * movespeed_ * dt;
        current_lifetime_ -= dt;
    }
}

void Particle::Render(SDL_Renderer* renderer)
{
    const SDL_Rect rect = { (int)pos.x - (int)(size_ / 2), (int)pos.y - (int)(size_ / 2), size_, size_ };
    SDL_SetTextureAlphaMod(texture_, alpha_);
    SDL_RenderCopy(renderer, texture_, NULL, &rect);

    // const SDL_Rect rect = { (int)pos.x - (size_ / 2), (int)pos.y - (size_ / 2), size_, size_ };
    // SDL_RenderFillRect(renderer, &rect);
}
