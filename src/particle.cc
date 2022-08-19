#include "particle.h"

Particle::Particle(const Vec2f& pos, const Vec2f& dir, float movespeed, SDL_Texture* texture, int size, float lifetime)
    : BaseObject(pos)
{
    dir_ = dir;
    movespeed_ = movespeed;
    texture_ = texture;
    size_ = size;
    lifetime_ = lifetime;
}

void Particle::Update(float dt)
{
    if (lifetime_ <= 0.0f)
        removable = true;
    else
    {
        lifetime_ -= dt;
        pos.x += dir_.x * movespeed_ * dt;
        pos.y += dir_.y * movespeed_ * dt;
        alpha_ = (lifetime_ * 635) > 0.0f ? (Uint8)(lifetime_ * 635) : 0;
    }
}

void Particle::Render(SDL_Renderer* renderer)
{
    // const SDL_Rect rect = { (int)pos.x - (size_ / 2), (int)pos.y - (size_ / 2), size_, size_ };
    // SDL_SetTextureAlphaMod(texture_, alpha_);
    // SDL_RenderCopy(renderer, texture_, NULL, &rect);

    const SDL_Rect rect = { (int)pos.x - (size_ / 2), (int)pos.y - (size_ / 2), size_, size_ };
    SDL_RenderFillRect(renderer, &rect);
}
