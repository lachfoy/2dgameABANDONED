#ifndef FIREBALLPARTICLE_H
#define FIREBALLPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseParticle.h"

class FireballParticle : public BaseParticle
{
public:
    inline FireballParticle(float x, float y, SDL_Texture* texture);
    virtual ~FireballParticle() {}
    
    inline void render(SDL_Renderer* renderer) override;

};

FireballParticle::FireballParticle(float x, float y, SDL_Texture* texture)
     : BaseParticle(x, y, 0.0f, 0.0f, texture)
{
    name = "FireballParticle";
    width = 24;
    height = 24;
    lifeTime = 0.2f;
}

void FireballParticle::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_particle_rect;
    fireball_particle_rect.w = width;
    fireball_particle_rect.h = height;
    fireball_particle_rect.x = (int)posX - (fireball_particle_rect.w / 2);
    fireball_particle_rect.y = (int)posY - (fireball_particle_rect.h / 2);

    // render the fireball particle
    Uint8 alpha = (lifeTime * 635) > 0.0f ? (Uint8)(lifeTime * 635) : 0;
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &fireball_particle_rect);

}

#endif