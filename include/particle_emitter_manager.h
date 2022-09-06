#ifndef PARTICLE_EMITTER_MANAGER_H_
#define PARTICLE_EMITTER_MANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "particle_emitter.h"
#include "particle_manager.h"
#include "vec2f.h"
#include "base_object.h"

// try out mozzila style guide for this class :)
class ParticleEmitterManager
{
public:
    ParticleEmitterManager(std::shared_ptr<ParticleManager> particle_manager)
    {
        particle_manager_ = particle_manager;
    }

    ~ParticleEmitterManager()
    {
        particle_emitters_.clear();
    }

    void AddParticleEmitter(BaseObject* parent, float spawn_interval, float emitter_lifetime, int num_particles, const ParticleSpawnInfo& info)
    {
        particle_emitters_.push_back(std::make_unique<ParticleEmitter>(parent, spawn_interval, emitter_lifetime, num_particles, info, particle_manager_));
    }

    void UpdateParticleEmitters(float dt)
    {
        for (const auto& emitter : particle_emitters_)
        {
            emitter->Update(dt);
        }

        particle_emitters_.erase(
            std::remove_if(
                particle_emitters_.begin(),
                particle_emitters_.end(),
                [](const auto& emitter) {
                    return emitter->parent()->removable();
                }
            ),
            particle_emitters_.end()
        );
    }

private:
    std::vector<std::unique_ptr<ParticleEmitter>> particle_emitters_;
    std::shared_ptr<ParticleManager> particle_manager_;

};

#endif
