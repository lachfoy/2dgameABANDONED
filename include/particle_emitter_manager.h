#ifndef PARTICLE_EMITTER_MANAGER_H_
#define PARTICLE_EMITTER_MANAGER_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "particle_emitter.h"
#include "particle_manager.h"
#include "Vec2f.h"
#include "BaseObject.h"

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

    void AddParticleEmitter(BaseObject* parent)
    {
        ParticleSpawnInfo info;
        //info.dir
        info.random_dir = true;
        //info.movespeed
        info.movespeed_min = 30.0f;
        info.movespeed_max = 100.0f;
        info.gravity = -0.8f;
        //info.size
        info.size_min = 24;
        info.size_max = 48;
        info.color = { 10, 123, 185, 255 };
        info.texture = nullptr;
        //info.lifetime = 0.3f;
        info.lifetime_min = 0.3f;
        info.lifetime_max = 0.2f;

        particle_emitters_.push_back(std::make_unique<ParticleEmitter>(parent, 0.0f, 10.0f, 1, info, particle_manager_));
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
                    return emitter->parent()->removable;
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
