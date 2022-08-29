#ifndef BASE_CHARACTER_H_
#define BASE_CHARACTER_H_

#include <SDL2/SDL.h>

#include <memory>

#include "base_object.h"
#include "Resistance.h"

class ResourceManager;
class ParticleEmitterManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class BaseCharacter : public BaseObject
{
public:
    BaseCharacter(const Vec2f& pos,
        ResourceManagerPtr resource_manager,
        ParticleEmitterManagerPtr particle_emitter_manager);

    // getters
    inline int health() const { return health_; }
    inline int max_health() const { return max_health_; }
    inline int width() const { return rect_.w; }
    inline int height() const { return rect_.h; }
    inline SDL_Rect const& collider_rect() const { return collider_rect_; }
    inline Vec2f const& dir() const { return dir_; }
    inline bool IsFacingRight() const { return facing_direction_; }

    virtual void TakeDamage(const Damage& damage); // overriden by player
    void Push(const Vec2f& pushDir, float pushMoveSpeed);

    virtual void Update(float dt) = 0;
    void Render(SDL_Renderer* renderer);
    void RenderDebug(SDL_Renderer* renderer);

protected:
    // can be pushed, hurt, on fire
    void UpdatePush(float dt);
    void UpdateHurt(float dt);
    void UpdateFire(float dt);
    void UpdatePosition(float dt); // update position and collider position

    void RenderShadow(SDL_Renderer* renderer);

    Vec2f dir_;
    SDL_Rect rect_;
    SDL_Color color_;
    SDL_Texture* texture_;
    SDL_Rect collider_rect_;

    int max_health_;
    int health_;
    Resistance resistance_;
    bool is_being_hurt_;
    float hurt_cooldown_ = 0.1f;
    float hurt_timer_ = hurt_cooldown_;
    bool is_immune_; // if not damageable then they are taking damage

    float movespeed_;
    float current_movespeed_;
    enum FacingDirection { FACING_LEFT, FACING_RIGHT } facing_direction_;

    // resources
    ResourceManagerPtr resource_manager_;

    // particles
    ParticleEmitterManagerPtr particle_emitter_manager_;

    // fire
    bool can_be_set_on_fire_ = true;
    bool is_on_fire_ = false;
    float on_fire_duration_ = 3.0f; // how many seconds of fire
    float on_fire_timer_ = on_fire_duration_;
    float fire_tick_interval_ = 0.4f; // how many seconds before each tick of fire damage
    float fire_tick_timer_ = fire_tick_interval_;

    // push
    bool is_being_pushed_ = false;
    float push_duration_ = 0.1f;
    float push_timer_ = push_duration_;
    Vec2f push_dir_;
    float push_movespeed_;
    
};

#endif