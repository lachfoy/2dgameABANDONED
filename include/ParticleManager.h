#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <vector>

#include <SDL2/SDL.h>

#include "ResourceManager.h"

class BaseParticle;

class ParticleManager
{
public:
    ParticleManager(ResourceManager* resourceManager);
    ~ParticleManager();

    void addFireballParticle(float x, float y);
    void addSmokeParticle(float x, float y);
    void addFireballExplosionParticle(float x, float y, float velX, float velY);

    void updateParticles(float dt);
    void removeUnusedParticles();
    void renderParticles(SDL_Renderer* renderer);

private:
    std::vector<BaseParticle*> particles;
    ResourceManager* resourceManager;
    
};

#endif