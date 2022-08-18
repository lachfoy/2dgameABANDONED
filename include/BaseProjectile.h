#ifndef BASEPROJECTILE_H
#define BASEPROJECTILE_H

#include <SDL2/SDL.h>

#include <memory>

#include "BaseObject.h"
#include "AABB2i.h"
#include "Damage.h"

class ProjectileManager;
class ParticleManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(const Vec2f& pos, const Vec2f& dir, SDL_Texture* texture, std::shared_ptr<ParticleManager> particleManager);
    virtual ~BaseProjectile() {}

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    inline AABB2i const& getCollider() const { return collider; }
    inline Damage const& getDamage() const { return damage; }
    inline Vec2f const& getDir() const { return dir; }
    
    void updateLifetime(float dt);
    virtual void spawnParticles(float dt) {}
    virtual void destroy(ProjectileManager& projectileManager) = 0;
    virtual void updatePosition(float dt); // derived projectiles can override update ONLY if they need to

    // debug
    void renderCollider(SDL_Renderer* renderer);

protected: // things the derived projectiles can change
    Vec2f dir;
    AABB2i collider;
    int colliderW;
    int colliderH;
    Damage damage;
    float moveSpeed;
    float lifeTime;
    SDL_Texture* texture; // texture to use for rendering, projectile does not have ownership
    std::shared_ptr<ParticleManager> particleManager;
    bool rotate = false;
    float angle = 0.0f; // angle in degrees
    float rotationSpeed = 0.0f;

};

#endif