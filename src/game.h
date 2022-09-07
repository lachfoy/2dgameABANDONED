#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class InputManager;
class ResourceManager;
class UiManager;
class ParticleManager;
class ParticleEmitterManager;
class ProjectileManager;
class Player;
class DebugTextManager;
class EnemyManager;
class EnemySpawnHandler;

typedef std::shared_ptr<InputManager> InputManagerPtr;
typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<UiManager> UiManagerPtr;
typedef std::shared_ptr<ParticleManager> ParticleManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;
typedef std::shared_ptr<ProjectileManager> ProjectileManagerPtr;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<DebugTextManager> DebugTextManagerPtr;
typedef std::shared_ptr<EnemyManager> EnemyManagerPtr;
typedef std::shared_ptr<EnemySpawnHandler> EnemySpawnHandlerPtr;

class Game
{
public:
    Game();

    bool Init(int window_width, int window_height); // build the window and renderer
    void Run(); // start game loop

private:
    int window_width_;
    int window_height_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    InputManagerPtr input_manager_;
    ResourceManagerPtr resource_manager_;
    UiManagerPtr ui_manager_;
    ParticleManagerPtr particle_manager_;
    ParticleEmitterManagerPtr particle_emitter_manager_;
    ProjectileManagerPtr projectile_manager_;
    PlayerPtr player_;
    DebugTextManagerPtr debug_text_manager_;
    EnemySpawnHandlerPtr enemy_spawn_handler_;
    EnemyManagerPtr enemy_manager_;
    
    void Create();
    void Update(float dt);
    void Render(SDL_Renderer* renderer);
    void Destroy(); // deallocate window and renderer

};

#endif
