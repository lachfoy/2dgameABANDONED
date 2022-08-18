#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include <memory>

#include "BaseObject.h"
#include "AABB2i.h"
#include "Resistance.h"

class ResourceManager;
class ParticleManager;

class BaseActor : public BaseObject
{
public:
    BaseActor(const Vec2f& pos,
        std::shared_ptr<ResourceManager> ResourceManager,
        std::shared_ptr<ParticleManager> particleManager);

    // getters
    inline int getHealth() const { return health; }
    inline int getMaxHealth() const { return maxHealth; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline AABB2i const& getCollider() const { return collider; }
    inline Vec2f const& getDir() const { return dir; }
    inline bool facingRight() const { return facingDirection; }

    virtual void takeDamage(const Damage& damage); // overriden by player
    void push(const Vec2f& pushDir, float pushMoveSpeed);

    virtual void updateTimers(float dt); // overriden by player
    void updatePosition(float dt);

    void renderShadow(SDL_Renderer* renderer);

    // debug
    void renderCollider(SDL_Renderer* renderer);

protected:
    Vec2f dir;
    int width;
    int height;
    SDL_Rect m_rect;
    SDL_Color m_color;
    int colliderW;
    int colliderH;
    AABB2i collider;

    int maxHealth;
    int health;
    Resistance resistance;
    bool isBeingHurt;
    float hurtCooldown = 0.1f;
    float hurtTimer = hurtCooldown;
    bool isImmune; // if not damageable then they are taking damage

    float startingMoveSpeed;
    float moveSpeed;
    enum FacingDirection { FACING_LEFT, FACING_RIGHT } facingDirection;

    // resources
    std::shared_ptr<ResourceManager> m_resourceManager;

    // particles
    std::shared_ptr<ParticleManager> particleManager;

    // fire
    bool canBeSetOnFire = true;
    bool isOnFire = false;
    float fireTime = 3.0f; // how many seconds of fire
    float fireTimer = fireTime;
    float fireTickTime = 0.4f; // how many seconds before each tick of fire damage
    float fireTickTimer = fireTickTime;
    float smokeParticleSpawnTime = 0.3f;
    float smokeParticleSpawnTimer = smokeParticleSpawnTime;

    // push
    bool isBeingPushed = false;
    float pushTime = 0.1f;
    float pushTimer = pushTime;
    Vec2f pushDir;
    float pushMoveSpeed;

    // debug
    

};

#endif