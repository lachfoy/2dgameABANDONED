#ifndef BASE_PROJECTILE_H_
#define BASE_PROJECTILE_H_

#include <SDL2/SDL.h>

#include <memory>

#include "BaseObject.h"
#include "AABB2i.h"
#include "Damage.h"

class ProjectileManager;
class ParticleManager;
class ResourceManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(const Vec2f& pos,
        const Vec2f& dir,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager);
    
    virtual ~BaseProjectile() {}

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    inline AABB2i const& getCollider() const { return collider; }
    inline Damage const& getDamage() const { return damage; }
    inline Vec2f const& getDir() const { return dir; }
    
    virtual void create(ProjectileManager& projectileManager) = 0;
    virtual void destroy(ProjectileManager& projectileManager) = 0;
    
    void updateLifetime(float dt);
    virtual void updatePosition(float dt); // derived projectiles can override update ONLY if they need to

    virtual void render(SDL_Renderer* renderer) = 0;

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
    bool rotate = false;
    float angle = 0.0f; // angle in degrees
    float rotationSpeed = 0.0f;

    std::shared_ptr<ParticleManager> m_particleManager;
    std::shared_ptr<ResourceManager> m_resourceManager;

};

#endif