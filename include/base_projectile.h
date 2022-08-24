#ifndef BASE_PROJECTILE_H_
#define BASE_PROJECTILE_H_

#include <SDL2/SDL.h>

#include <memory>

#include "base_object.h"
#include "AABB2i.h"
#include "Damage.h"

class ProjectileManager;
class ParticleManager;
class ResourceManager;
class ParticleEmitterManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(const Vec2f& pos,
        const Vec2f& dir,
        std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager);
    
    virtual ~BaseProjectile() {}

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    inline AABB2i const& getCollider() const { return collider; }
    inline Damage const& getDamage() const { return damage; }
    inline Vec2f const& getDir() const { return dir; }
    
    virtual void OnCreate(ProjectileManager& projectileManager) {}
    virtual void OnDestroy(ProjectileManager& projectileManager) {}

    virtual void Update(float dt);
    virtual void Render(SDL_Renderer* renderer);

    // debug
    void renderCollider(SDL_Renderer* renderer);

protected: // things the derived projectiles can access
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
    int size_;
    SDL_Rect rect_;
    SDL_Texture* texture_; // texture to use for rendering, particle does not have ownership

    std::shared_ptr<ParticleManager> particle_manager_;
    std::shared_ptr<ResourceManager> resource_manager_;
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager_;

};

#endif