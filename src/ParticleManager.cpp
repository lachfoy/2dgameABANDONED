#include "ParticleManager.h"

#include "BaseParticle.h"
#include "FireballParticle.h"
#include "SmokeParticle.h"

ParticleManager::ParticleManager(std::shared_ptr<ResourceManager> resourceManager)
{
    this->m_resourceManager = resourceManager;
}

ParticleManager::~ParticleManager()
{
    // clear the particles vector and delete the pointers
    for (const auto& particle : particles) delete particle;
    particles.clear();
}

void ParticleManager::addFireballParticle(const Vec2f& pos)
{
    particles.push_back(new FireballParticle(pos, m_resourceManager->getTexture("FireballParticleTexture")));
}

void ParticleManager::addSmokeParticle(const Vec2f& pos)
{
    particles.push_back(new SmokeParticle(pos, m_resourceManager->getTexture("SmokeParticleTexture")));
}

void ParticleManager::addFireballExplosionParticle(const Vec2f& pos, const Vec2f& dir)
{
    particles.push_back(new SmokeParticle(pos, m_resourceManager->getTexture("SmokeParticleTexture")));
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