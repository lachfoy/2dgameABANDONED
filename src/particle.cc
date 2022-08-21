#include "particle.h"

#include <iostream>

Particle::Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, int size, float lifetime, const SDL_Color& color, SDL_Texture* texture)
    : BaseObject(pos)
{
        name = "particle";//debug
    dir_ = dir;
    movespeed_ = movespeed;
    gravity_ = -0.4f;
    size_ = size;
    start_lifetime_ = lifetime;
    current_lifetime_ = start_lifetime_;
    color_ = color;
    texture_ = texture;
}

void Particle::Update(float dt)
{
    if (current_lifetime_ <= 0.0f)
        removable = true;
    else
    {
        // what percent of X is Y. Use the percentage formula: Y/X = P%
        alpha_ = (current_lifetime_ / start_lifetime_) * 255;
        pos.x += dir_.x * movespeed_ * dt;
        pos.y += dir_.y * movespeed_ * dt + gravity_;
        current_lifetime_ -= dt;
    }
}

void Particle::Render(SDL_Renderer* renderer)
{
    const SDL_Rect rect = { (int)pos.x - (int)(size_ / 2), (int)pos.y - (int)(size_ / 2), size_, size_ };
    SDL_SetTextureAlphaMod(texture_, alpha_);
    SDL_SetTextureColorMod(texture_, color_.r, color_.g, color_.b);
    SDL_RenderCopy(renderer, texture_, NULL, &rect);

    // const SDL_Rect rect = { (int)pos.x - (size_ / 2), (int)pos.y - (size_ / 2), size_, size_ };
    // SDL_RenderFillRect(renderer, &rect);
}
