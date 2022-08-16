#ifndef SMOKEPARTICLE_H
#define SMOKEPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseParticle.h"

class SmokeParticle : public BaseParticle
{
public:
    inline SmokeParticle(const Vec2f& pos, SDL_Texture* texture);
    virtual ~SmokeParticle() {}
    
    inline void render(SDL_Renderer* renderer) override;

};

SmokeParticle::SmokeParticle(const Vec2f& pos, SDL_Texture* texture)
     : BaseParticle(pos, { 0.0f, 0.0f }, texture)
{
    name = "SmokeParticle";
    width = 60;
    height = 60;
    lifeTime = 1.0f;
}

void SmokeParticle::render(SDL_Renderer* renderer)
{
    const SDL_Rect rect = { (int)pos.x - (width / 2), (int)pos.y - (height / 2), width, height };

    Uint8 alpha = (lifeTime * 635) > 0.0f ? (Uint8)(lifeTime * 635) : 0;// should be in update ..
    alpha /= 2;
    pos.y -= 0.6f;

    // render the fireball particle
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &rect);

}

#endif