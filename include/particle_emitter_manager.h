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
        ParticleEmitterInfo info;
        info.pos = pos;
        //info.particle_dir
        info.random_dir = true;
        //info.particle_movespeed
        info.particle_movespeed_min = 200.0f;
        info.particle_movespeed_max = 300.0f;
        //info.gravity
        //info.particle_size
        info.particle_size_min = 8;
        info.particle_size_max = 14;
        info.particle_texture = nullptr;
        info.particle_lifetime = 0.5f;
        info.spawn_interval = 0.2f;
        info.emitter_lifetime = 30.0f;
        info.num_particles = 30;
        info.particle_manager = particle_manager_;
        
        particle_emitters_.push_back(std::make_unique<ParticleEmitter>(info));
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
