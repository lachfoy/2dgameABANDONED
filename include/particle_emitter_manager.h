#ifndef PARTICLE_EMITTER_MANAGER_H_
#define PARTICLE_EMITTER_MANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "particle_emitter.h"
#include "particle_manager.h"
#include "Vec2f.h"

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

    void AddParticleEmitter(const Vec2f& pos)
    {
        particle_emitters_.push_back(std::make_unique<ParticleEmitter>(nullptr,
            0.2f,
            10.0f,
            20.0f,
            30,
            pos,
            Vec2f(0.0f, 0.0f), // not used
            true,
            100.0f,
            300.0f,
            0.0f, // not used
            particle_manager_));
    }

    void UpdateParticleEmitters(float dt)
    {
        for (const auto& emitter : particle_emitters_)
        {
            emitter->Update(dt);

            // if (emitter->removable)
            // {
            //     particle_emitters_.erase(std::remove(particle_emitters_.begin(), particle_emitters_.end(), emitter));
            // }
        }

        particle_emitters_.erase(
            std::remove_if(
                particle_emitters_.begin(),
                particle_emitters_.end(),
                [](const auto& emitter) {
                    return emitter->removable;
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
