#include "ParticleManager.h"

ParticleManager::ParticleManager(std::shared_ptr<ResourceManager> resourceManager)
{
    this->resource_manager_ = resourceManager;
}

ParticleManager::~ParticleManager()
{
    particles_.clear();
}

void ParticleManager::AddParticle(const Vec2f& pos, const Vec2f& dir, float movespeed, SDL_Texture* texture, int size, float lifetime)
{
    particles_.push_back(std::make_unique<Particle>(pos, dir, movespeed, texture, size, lifetime));
}


void ParticleManager::UpdateParticles(float dt)
{
    for (const auto& particle : particles_)
    {
        particle->Update(dt);
    }

    for (int i = 0; i < particles_.size(); i++)
    {
        if (particles_[i]->removable)
        {
            particles_.erase(particles_.begin() + i);
            i--;
        }
    }
}

void ParticleManager::RenderParticles(SDL_Renderer* renderer)
{
    for (const auto& particle : particles_)
    {
        particle->Render(renderer);
    }
}