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

class ParticleEmitter : public BaseObject
{
public:
    inline ParticleEmitter(SDL_Texture* particle_texture,
        float spawn_interval,
        float particle_lifetime,
        float emitter_lifetime,
        int num_particles,
        const Vec2f& pos,
        const Vec2f& particle_dir, // only used if random_dir = false
        bool random_dir,
        float particle_move_speed_min,
        float particle_move_speed_max,
        float gravity, // unused
        std::shared_ptr<ParticleManager> particle_manager)
         : BaseObject(pos)
    {
        particle_texture_ = particle_texture;
        spawn_interval_ = spawn_interval;
        
        emitter_lifetime_timer_ = emitter_lifetime;

        num_particles_ = num_particles;
        particle_dir_ = particle_dir;
        random_dir_ = random_dir;
        particle_move_speed_min_ = particle_move_speed_min;
        particle_move_speed_max_ = particle_move_speed_max;
        gravity_ = gravity;
        particle_manager_ = particle_manager;
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

                    float random_move_speed = rand() % (int)(particle_move_speed_max_ - particle_move_speed_min_ + 1) + particle_move_speed_min_;
                    particle_manager_->AddParticle(pos, particle_dir_, random_move_speed, particle_texture_, 10, 1.0f);
                    //void AddParticle(const Vec2f& pos, const Vec2f& dir, float movespeed, SDL_Texture* texture, int size, float lifetime);

                }
                spawn_timer_ = spawn_interval_;
            }
        }
        else
        {
            // delete this entity
            std::cout << "Particle Emitter lifetime ended\n";
        }
        
    }

private:
    float emitter_lifetime_timer_;
    SDL_Texture* particle_texture_;
    float spawn_interval_;
    float spawn_timer_;
    int num_particles_;
    Vec2f particle_dir_;
    bool random_dir_;
    float particle_move_speed_min_;
    float particle_move_speed_max_;
    float gravity_;
    std::shared_ptr<ParticleManager> particle_manager_;

};

#endif