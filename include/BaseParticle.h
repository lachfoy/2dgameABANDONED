#ifndef BASEPARTICLE_H
#define BASEPARTICLE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"

class BaseParticle : public BaseObject
{
public:
    BaseParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed, SDL_Texture* texture = nullptr);
    virtual ~BaseParticle() {}

    inline Vec2f const& getDir() const { return dir; }
    
    void updateLifetime(float dt);
    void updatePosition(float dt);

    virtual void render(SDL_Renderer* renderer) = 0;

protected: // things the derived particles can change
    Vec2f dir;
    int width = 10;
    int height = 10;
    float m_moveSpeed = 0.0f;
    float lifeTime = 0.0f;
    SDL_Texture* texture = nullptr; // texture to use for rendering, particle does not have ownership

};

#endif