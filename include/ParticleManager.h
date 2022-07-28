#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

#include "ResourceManager.h"

class BaseParticle;

class ParticleManager
{
public:
    ParticleManager(ResourceManager* resourceManager)
    {
        this->resourceManager = resourceManager;
    }

    ~ParticleManager();

    std::vector<BaseParticle*> const& getParticles() const { return particles; }

    void updateParticles(float dt);
    void removeUnusedParticles();
    void renderParticles(SDL_Renderer* renderer);

private:
    std::vector<BaseParticle*> particles;
    ResourceManager* resourceManager;
    
};

#endif