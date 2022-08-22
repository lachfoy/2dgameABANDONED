#include "particle_manager.h"

ParticleManager::ParticleManager(std::shared_ptr<ResourceManager> resourceManager)
{
    resource_manager_ = resourceManager;
}

ParticleManager::~ParticleManager()
{
    particles_.clear();
}

void ParticleManager::AddParticle(const Vec2f& pos, const Vec2f& dir, float movespeed, float gravity, int size, float lifetime, const SDL_Color& color, SDL_Texture* texture)
{
    if (!texture) texture = resource_manager_->GetTexture("flame_particle2_texture");
    particles_.push_back(std::make_unique<Particle>(pos, dir, movespeed, gravity, size, lifetime, color, texture));
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