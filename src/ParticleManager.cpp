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
    for (const auto& particle : m_particles) delete particle;
    m_particles.clear();
}

void ParticleManager::addFireballParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed)
{
    m_particles.push_back(new FireballParticle(pos, dir, moveSpeed, m_resourceManager->getTexture("FireballParticleTexture")));
}

void ParticleManager::addSmokeParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed)
{
    m_particles.push_back(new SmokeParticle(pos, dir, moveSpeed, m_resourceManager->getTexture("SmokeParticleTexture")));
}

void ParticleManager::addFireballExplosionParticle(const Vec2f& pos, const Vec2f& dir, float moveSpeed)
{
    m_particles.push_back(new SmokeParticle(pos, dir, moveSpeed, m_resourceManager->getTexture("SmokeParticleTexture")));
}

void ParticleManager::updateParticles(float dt)
{
    for (const auto& particle : m_particles)
    {
        particle->updateLifetime(dt);
        particle->updatePosition(dt);
    }
}

void ParticleManager::removeUnusedParticles()
{
    for (int i = 0; i < m_particles.size(); i++)
    {
        if (m_particles[i]->removable)
        {
            delete m_particles[i];
            m_particles.erase(m_particles.begin() + i);
            i--;
        }
    }
}

void ParticleManager::renderParticles(SDL_Renderer* renderer)
{
    for (const auto& particle : m_particles)
    {
        particle->render(renderer);
    }
}