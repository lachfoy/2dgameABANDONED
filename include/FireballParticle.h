#ifndef FIREBALLPARTICLE_H
#define FIREBALLPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseParticle.h"

class FireballParticle : public BaseParticle
{
public:
    inline FireballParticle(const Vec2f& pos, SDL_Texture* texture);
    virtual ~FireballParticle() {}
    
    inline void render(SDL_Renderer* renderer) override;

};

FireballParticle::FireballParticle(const Vec2f& pos, SDL_Texture* texture)
     : BaseParticle(pos, {0.0f, 0.0f}, texture)
{
    name = "FireballParticle";
    width = 24;
    height = 24;
    lifeTime = 0.2f;
}

void FireballParticle::render(SDL_Renderer* renderer)
{
    const SDL_Rect rect = { (int)pos.x - (width / 2), (int)pos.y - (height / 2), width, height };

    // render the fireball particle
    Uint8 alpha = (lifeTime * 635) > 0.0f ? (Uint8)(lifeTime * 635) : 0;
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_RenderCopy(renderer, texture, NULL, &rect);

}

#endif