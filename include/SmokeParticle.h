#ifndef SMOKEPARTICLE_H
#define SMOKEPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseParticle.h"

class SmokeParticle : public BaseParticle
{
public:
    inline SmokeParticle(float x, float y, SDL_Texture* texture);
    virtual ~SmokeParticle() {}
    
    inline void render(SDL_Renderer* renderer) override;

};

SmokeParticle::SmokeParticle(float x, float y, SDL_Texture* texture)
     : BaseParticle(x, y, 0.0f, 0.0f, texture)
{
    name = "SmokeParticle";
    width = 60;
    height = 60;
    lifeTime = 1.0f;
}

void SmokeParticle::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_particle_rect;
    fireball_particle_rect.w = width;
    fireball_particle_rect.h = height;
    fireball_particle_rect.x = (int)posX - (fireball_particle_rect.w / 2);
    fireball_particle_rect.y = (int)posY - (fireball_particle_rect.h / 2);

    
    Uint8 alpha = (lifeTime * 635) > 0.0f ? (Uint8)(lifeTime * 635) : 0;// should be in update ..
    alpha/=2;
    posY-=0.6f;

    // render the fireball particle
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &fireball_particle_rect);

}

#endif