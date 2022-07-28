#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

#include "ResourceManager.h"

class BaseParticle;
class FireballParticle;

class ParticleManager
{
public:
    ParticleManager(ResourceManager* resourceManager)
    {
        this->resourceManager = resourceManager;
    }

    ~ParticleManager();

    void addFireballParticle(float x, float y);

    void updateParticles(float dt);
    void removeUnusedParticles();
    void renderParticles(SDL_Renderer* renderer);

private:
    std::vector<BaseParticle*> particles;
    ResourceManager* resourceManager;
    
};

#endif