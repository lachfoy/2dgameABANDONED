#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>

#include <SDL2/SDL.h>

#include "resource_manager.h"
#include "vec2f.h"
#include "particle.h"

class ParticleManager
{
public:
    ParticleManager(std::shared_ptr<ResourceManager> resourceManager);
    ~ParticleManager();

    void AddParticle(const Vec2f& pos, const Vec2f& dir, float movespeed, float gravity, int size, float lifetime,
        const SDL_Color& color, SDL_Texture* texture);

    void UpdateParticles(float dt);
    void RenderParticles(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<Particle>> particles_;
    std::shared_ptr<ResourceManager> resource_manager_;
    
};

#endif