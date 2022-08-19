#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_

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

    void addFireballParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed);
    void addSmokeParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed);
    void addFireballExplosionParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed);

    void updateParticles(float dt);
    void removeUnusedParticles();
    void renderParticles(SDL_Renderer* renderer);

private:
    std::vector<BaseParticle*> m_particles;
    std::shared_ptr<ResourceManager> m_resourceManager;
    
};

#endif