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

    // if particle gets flagged for removal
    particles_.erase(
        std::remove_if(
            particles_.begin(),
            particles_.end(),
            [](auto const& particle) {
                return particle->removable();
            }
        ),
        particles_.end()
    );
}

void ParticleManager::RenderParticles(SDL_Renderer* renderer)
{
    for (const auto& particle : particles_)
    {
        particle->Render(renderer);
    }
}