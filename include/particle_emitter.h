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
struct ParticleEmitterInfo
{
    Vec2f pos;
    Vec2f particle_dir; // only used if random_dir = false
    bool random_dir; // idealy allowing a random of random directions would be better
    float particle_movespeed;
    float particle_movespeed_min;
    float particle_movespeed_max;
    float gravity;
    int particle_size;
    int particle_size_min;
    int particle_size_max;
    SDL_Color particle_color;
    SDL_Texture* particle_texture;
    float particle_lifetime;
    float spawn_interval;
    float emitter_lifetime;
    int num_particles;
    std::shared_ptr<ParticleManager> particle_manager;
};

class ParticleEmitter : public BaseObject
{
public:
    inline ParticleEmitter(const ParticleEmitterInfo& info)
     : BaseObject(info.pos)
    {
        particle_dir_ = info.particle_dir;
        random_dir_ = info.random_dir;
        particle_movespeed_ = info.particle_movespeed;
        particle_movespeed_min_ = info.particle_movespeed_min;
        particle_movespeed_max_ = info.particle_movespeed_max;
        gravity_ = info.gravity;
        particle_size_ = info.particle_size;
        particle_size_min_ = info.particle_size_min;
        particle_size_max_ = info.particle_size_max;
        particle_color_ = info.particle_color;
        particle_texture_ = info.particle_texture;
        particle_lifetime_ = info.particle_lifetime;
        spawn_interval_ = info.spawn_interval;
        spawn_timer_ = spawn_interval_;
        emitter_lifetime_ = info.emitter_lifetime;
        emitter_lifetime_timer_ = emitter_lifetime_;
        num_particles_ = info.num_particles;
        particle_manager_ = info.particle_manager;
    }

    ~ParticleEmitter()
    {

    }

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
                    if (random_dir_) // pick a random direction
                    {
                        float random_grad = 2.0f * M_PI * ((rand() % 100 + 1) / 100.0f); // random gradian
                        particle_dir_ = Vec2f(cosf(random_grad), sinf(random_grad));
                    }

                    float random_movespeed = rand() % (int)(particle_movespeed_max_ - particle_movespeed_min_ + 1) + particle_movespeed_min_;
                    int random_size = rand() % (particle_size_max_ - particle_size_min_ + 1) + particle_size_min_;

                    particle_manager_->AddParticle(pos, particle_dir_, random_movespeed, random_size, particle_lifetime_, particle_color_, particle_texture_);

                }
                spawn_timer_ = spawn_interval_;
            }
        }
        else
        {
            // delete this entity
            std::cout << "deleting particle emitter\n";
            removable = true;
        }
        
    }

private:
    Vec2f particle_dir_;
    bool random_dir_;
    float particle_movespeed_;
    float particle_movespeed_min_;
    float particle_movespeed_max_;
    float gravity_;
    int particle_size_;
    int particle_size_min_;
    int particle_size_max_;
    SDL_Color particle_color_;
    SDL_Texture* particle_texture_;
    float particle_lifetime_;
    float spawn_interval_;
    float spawn_timer_;
    float emitter_lifetime_;
    float emitter_lifetime_timer_;
    int num_particles_;
    std::shared_ptr<ParticleManager> particle_manager_;

};

#endif