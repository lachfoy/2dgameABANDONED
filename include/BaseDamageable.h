#ifndef BASEDAMAGEABLE_H
#define BASEDAMAGEABLE_H

#include "BaseObject.h"
#include "AABB.h"
#include "Resistance.h"

class ResourceManager;
class ParticleManager;

class BaseDamageable : public BaseObject
{
public:
    BaseDamageable(float x, float y, ResourceManager* ResourceManager, ParticleManager* particleManager); // we assume that every damageable gets created with a pointer to the resource manager

    // getters
    inline int getHealth() const { return health; }
    inline int getMaxHealth() const { return maxHealth; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline AABB const& getCollider() const { return collider; }
    float getVelX() const { return velX; }
    float getVelY() const { return velY; }
    bool facingRight() const { return facingDirection; }

    virtual void takeDamage(const Damage& damage); // overriden by player
    void push(float pushVelX, float pushVelY, float pushMoveSpeed);

    virtual void updateTimers(float dt); // overriden by player
    void updatePosition(float dt);

    void renderShadow(SDL_Renderer* renderer);

    // debug
    void renderCollider(SDL_Renderer* renderer);

protected:
    float velX = 0.0f;
    float velY = 0.0f;
    int width;
    int height;
    SDL_Rect m_rect;
    SDL_Color m_color;
    int colliderW;
    int colliderH;
    AABB collider;

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
    ResourceManager* resourceManager = nullptr;

    // particles
    ParticleManager* particleManager = nullptr;

    // fire
    bool canBeSetOnFire = true;
    bool isOnFire = false;
    float fireTime = 3.0f; // how many seconds of fire
    float fireTimer = fireTime;
    float fireTickTime = 0.4f; // how many seconds before each tick of fire damage
    float fireTickTimer = fireTickTime;
    float smokeParticleSpawnTime = 0.2f;
    float smokeParticleSpawnTimer = smokeParticleSpawnTime;

    // push
    bool isBeingPushed = false;
    float pushTime = 0.1f;
    float pushTimer = pushTime;
    float pushVelX;
    float pushVelY;
    float pushMoveSpeed;

    // debug
    

};

#endif