#include "ParticleManager.h"

#include "BaseParticle.h"
#include "FireballParticle.h"
#include "SmokeParticle.h"

ParticleManager::ParticleManager(ResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

ParticleManager::~ParticleManager()
{
    // clear the particles vector and delete the pointers
    for (const auto& particle : particles) delete particle;
    particles.clear();
}

void ParticleManager::addFireballParticle(float x, float y)
{
    particles.push_back(new FireballParticle(x, y, resourceManager->getTexture("FireballParticleTexture")));
}

void ParticleManager::addSmokeParticle(float x, float y)
{
    particles.push_back(new SmokeParticle(x, y, resourceManager->getTexture("SmokeParticleTexture")));
}

void ParticleManager::addFireballExplosionParticle(float x, float y, float velX, float velY)
{
    particles.push_back(new SmokeParticle(x, y, resourceManager->getTexture("SmokeParticleTexture")));
}

void ParticleManager::updateParticles(float dt)
{
    for (const auto& particle : particles)
    {
        particle->updateLifetime(dt);
        particle->updatePosition(dt);
    }
}

void ParticleManager::removeUnusedParticles()
{
    for (int i = 0; i < particles.size(); i++)
    {
        if (particles[i]->removable)
        {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void ParticleManager::renderParticles(SDL_Renderer* renderer)
{
    for (const auto& particle : particles)
    {
        particle->render(renderer);
    }
}