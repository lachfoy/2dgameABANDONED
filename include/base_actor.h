#ifndef BASE_ACTOR_H_
#define BASE_ACTOR_H_

#include <memory>

#include "base_object.h"
#include "AABB2i.h"
#include "Resistance.h"

class ResourceManager;
class ParticleManager;
class ParticleEmitterManager;

class BaseActor : public BaseObject
{
public:
    BaseActor(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager);

    // getters
    inline int health() const { return health_; }
    inline int max_health() const { return max_health_; }
    inline int width() const { return width_; }
    inline int height() const { return height_; }
    inline AABB2i const& collider() const { return collider_; }
    inline Vec2f const& dir() const { return dir_; }
    inline bool IsFacingRight() const { return facing_direction_; }

    virtual void TakeDamage(const Damage& damage); // overriden by player
    void Push(const Vec2f& pushDir, float pushMoveSpeed);

    // can be pushed, hurt, on fire
    void UpdatePush(float dt);
    void UpdateHurt(float dt);
    void UpdateFire(float dt);
    void UpdatePosition(float dt); // update position and collider position
    virtual void Update(float dt) = 0;

    void RenderShadow(SDL_Renderer* renderer);
    void RenderCollider(SDL_Renderer* renderer);
    virtual void Render(SDL_Renderer* renderer) = 0;

protected:
    Vec2f dir_;
    int width_;
    int height_;
    SDL_Rect m_rect;
    SDL_Color m_color;
    int colliderW;
    int colliderH;
    AABB2i collider_;

    int max_health_;
    int health_;
    Resistance resistance;
    bool isBeingHurt;
    float hurtCooldown = 0.1f;
    float hurtTimer = hurtCooldown;
    bool isImmune; // if not damageable then they are taking damage

    float startingMoveSpeed;
    float moveSpeed;
    enum FacingDirection { FACING_LEFT, FACING_RIGHT } facing_direction_;

    // resources
    std::shared_ptr<ResourceManager> resource_manager_;

    // particles
    std::shared_ptr<ParticleManager> particle_manager_;
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager_;

    // fire
    bool canBeSetOnFire = true;
    bool isOnFire = false;
    float fireTime = 3.0f; // how many seconds of fire
    float fireTimer = fireTime;
    float fireTickTime = 0.4f; // how many seconds before each tick of fire damage
    float fireTickTimer = fireTickTime;

    // push
    bool isBeingPushed = false;
    float pushTime = 0.1f;
    float pushTimer = pushTime;
    Vec2f pushDir;
    float pushMoveSpeed;

    // debug
    

};

#endif