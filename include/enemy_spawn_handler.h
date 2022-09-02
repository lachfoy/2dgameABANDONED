#ifndef ENEMY_SPAWN_HANDLER_H_
#define ENEMY_SPAWN_HANDLER_H_

#include "enemy_manager.h"
#include "Vec2f.h"

#include <cstdlib>
#include <iostream>

typedef std::shared_ptr<EnemyManager> EnemyManagerPtr;

// handles spawning groups of enemies on either side of the play area
// later will handle other logic like increasing the difficulty of enemies over time
class EnemySpawnHandler
{
public:
    EnemySpawnHandler(EnemyManagerPtr enemy_manager, int window_width, int window_height)
    {
        enemy_manager_ = enemy_manager;
        window_width_ = window_width;
        window_height_ = window_height;

        enemy_spawn_interval_ = 0.2f; // ASHDGAKUJSHFGASKJFH
        enemy_spawn_timer_ = 0.0f; // timer goes up, not down

        current_wave_spawn_counter_ = 0;
    }

    // update the logic
    void Update(float dt)
    {
        const int kMaxEnemies= 1000;
        if (current_wave_spawn_counter_ < kMaxEnemies)
        {
            if (enemy_spawn_timer_ >= enemy_spawn_interval_)
            {
                int side = rand() % 2; // pick a number between 0 and 1, 0 = left, 1= right
                std::string side_str = (side == 0) ? "left" : "right";
                std::cout << "side: " << side_str << std::endl;

                const int x_offset_amount = 60; // offset so they spawn outside the play area
                float x_offset = float(rand() % x_offset_amount + 1); // pick a random x offset
                std::cout << "x offset: " << x_offset << std::endl;

                Vec2f spawn_pos;
                spawn_pos.x = (side == 0) ? float(0 - x_offset) : float(window_width_ + x_offset);
                spawn_pos.y = float(rand() % window_height_ + 1); // pick a random y
                std::cout << "pos: " << spawn_pos.x << ", " << spawn_pos.y << std::endl;

                // add an enemy
                enemy_manager_->AddSkeleton(spawn_pos);

                // update the counter
                current_wave_spawn_counter_++;
                std::cout << "spawned " << current_wave_spawn_counter_ << " total enemies\n";

                enemy_spawn_timer_ = 0.0f; // reset the timer
            }
            else
            {
                enemy_spawn_timer_ += dt;
            }
        }

    }

    // void SpawnEnemies(float dt)
    // {
    //     // left side off screen

    //     for (int i =0; i < num_enemies)
    //     enemy_manager_->AddSkeleton()
    // }


private:
    EnemyManagerPtr enemy_manager_;
    int window_width_;
    int window_height_;

    float enemy_spawn_interval_;
    float enemy_spawn_timer_;

    int current_wave_spawn_counter_;

};

#endif
