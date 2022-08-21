#ifndef PARTICLE_EMITTER_H_
#define PARTICLE_EMITTER_H_

#include <memory>
#include <string>
#include <cstdlib> // rand
#include <cmath> // sin cos
#include <iostream>

#include <SDL2/SDL.h>

#include "Vec2f.h"
#include "particle_manager.h"
#include "BaseObject.h"

// class uses mozzila style for a change

// TODO:
// varied size
// need ParticleSpawnerManager class :(

// since there are like a million params, using a struct seems nice
struct ParticleSpawnInfo
{
    Vec2f dir; // only used if random_dir = false
    bool random_dir; // idealy allowing a random of random directions would be better
    float movespeed;
    float movespeed_min;
    float movespeed_max;
    float gravity;
    int size;
    int size_min;
    int size_max;
    SDL_Color color;
    SDL_Texture* texture;
    float lifetime;
    float lifetime_min;
    float lifetime_max;
};

class ParticleEmitter
{
public:
    inline ParticleEmitter(BaseObject* parent, float spawn_interval, float emitter_lifetime, int num_particles,
        const ParticleSpawnInfo& info, std::shared_ptr<ParticleManager> particle_manager)
    {
        parent_ = parent;

        spawn_interval_ = spawn_interval;
        spawn_timer_ = spawn_interval_;
        emitter_lifetime_ = emitter_lifetime;
        emitter_lifetime_timer_ = emitter_lifetime_;
        num_particles_ = num_particles;
        
        info_ = info;

        particle_manager_ = particle_manager;
    }

    ~ParticleEmitter()
    {
        std::cout << "Particle Emitter Destroyed\n";
    }

    BaseObject* const& parent() const { return parent_; }

    void Update(float dt)
    {
        if (emitter_lifetime_timer_ > 0.0f) 
        {
            emitter_lifetime_timer_ -= dt;

            if (spawn_timer_ > 0.0f) spawn_timer_ -= dt;
            else
            {
                for (int i = 0; i < num_particles_; i++)
                {
                    if (info_.random_dir) // pick a random direction
                    {
                        float random_grad = 2.0f * M_PI * ((rand() % 100 + 1) / 100.0f); // random gradian
                        info_.dir = Vec2f(cosf(random_grad), sinf(random_grad));
                    }

                    float random_movespeed = rand() % int(info_.movespeed_max - info_.movespeed_min + 1) + info_.movespeed_min;
                    int random_size = rand() % (info_.size_max - info_.size_min + 1) + info_.size_min;

                    float random_lifetime = (rand() % int((info_.lifetime_max * 100) - (info_.lifetime_min * 100) + 1) + info_.lifetime_min * 100) / 100.0f;

                    particle_manager_->AddParticle(parent_->pos, info_.dir, random_movespeed, info_.gravity, random_size, random_lifetime, info_.color, info_.texture);

                }
                spawn_timer_ = spawn_interval_;
            }
        }
        // else
        // {
        //     removable = true;
        // }
        
    }

private:
    BaseObject* parent_;

    float spawn_interval_;
    float spawn_timer_;
    float emitter_lifetime_;
    float emitter_lifetime_timer_;
    int num_particles_;

    ParticleSpawnInfo info_;

    std::shared_ptr<ParticleManager> particle_manager_;

};

#endif