#ifndef BASEPARTICLE_H
#define BASEPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"

class BaseParticle : public BaseObject
{
public:
    BaseParticle(float x, float y, float velX, float velY, SDL_Texture* texture = nullptr);
    virtual ~BaseParticle() {}

    float getVelX() const { return velX; }
    float getVelY() const { return velY; }
    
    void updateLifetime(float dt);
    void updatePosition(float dt);

protected: // things the derived particles can change
    float velX = 0.0f; // normalized x velocity
    float velY = 0.0f; // normalized y velocity
    int width = 10;
    int height = 10;
    float moveSpeed = 0.0f;
    float lifeTime = 0.0f;
    SDL_Texture* texture = nullptr; // texture to use for rendering, particle does not have ownership

};

#endif