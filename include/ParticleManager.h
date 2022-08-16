#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "ResourceManager.h"
#include "Vec2f.h"

class BaseParticle;

class ParticleManager
{
public:
    ParticleManager(std::shared_ptr<ResourceManager> resourceManager);
    ~ParticleManager();

    void addFireballParticle(const Vec2f& pos);
    void addSmokeParticle(const Vec2f& pos);
    void addFireballExplosionParticle(const Vec2f& pos, const Vec2f& dir);

    void updateParticles(float dt);
    void removeUnusedParticles();
    void renderParticles(SDL_Renderer* renderer);

private:
    std::vector<BaseParticle*> particles;
    std::shared_ptr<ResourceManager> m_resourceManager;
    
};

#endif