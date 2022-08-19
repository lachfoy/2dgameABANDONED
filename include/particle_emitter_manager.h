#ifndef PARTICLE_EMITTER_MANAGER_H_
#define PARTICLE_EMITTER_MANAGER_H_

#include <vector>
#include <memory>

#include "ParticleEmitter.h"
#include "ParticleManager.h"

// try out mozzila style guide for this class :)

class ParticleEmitterManager
{
public:
    ParticleEmitterManager(std::shared_ptr<ParticleManager> particleManager)
    {

    }

    ~ParticleEmitterManager()
    {
        particle_emitters_.clear();
    }

    void AddParticleEmitter()
    {
        particle_emitters_.push_back(std::make_unique<ParticleEmitter>(PARTICLE_FIRE,
            0.2f,
            10.0f,
            10.0f,
            30,
            Vec2f(500.0f, 300.0f),
            Vec2f(0.0f, 0.0f),
            true,
            100.0f,
            300.0f,
            0.0f,
            m_particleManager));
    }

    void UpdateParticleEmitters()
    {

    }


private:
    std::vector<std::unique_ptr<ParticleEmitter>> particle_emitters_;
    std::shared_ptr<ParticleManager> particle_manager_;

};

#endif
