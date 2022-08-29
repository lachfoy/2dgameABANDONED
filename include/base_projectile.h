#ifndef BASE_PROJECTILE_H_
#define BASE_PROJECTILE_H_

#include <SDL2/SDL.h>

#include <memory>

#include "base_object.h"
#include "AABB2i.h"
#include "Damage.h"


class ParticleManager;
class ResourceManager;
class ParticleEmitterManager;
class ProjectileManager;

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
typedef std::shared_ptr<ParticleManager> ParticleManagerPtr;
typedef std::shared_ptr<ParticleEmitterManager> ParticleEmitterManagerPtr;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(const Vec2f& pos,
        const Vec2f& dir,
        ResourceManagerPtr resource_manager,
        ParticleManagerPtr particle_manager,
        ParticleEmitterManagerPtr particle_emitter_manager);
    
    virtual ~BaseProjectile() {}

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    inline SDL_Rect const& collider_rect() const { return collider_rect_; }
    inline Damage const& damage() const { return damage_; }
    inline Vec2f const& dir() const { return dir_; }
    
    virtual void OnCreate(ProjectileManager& projectileManager) {}
    virtual void OnDestroy(ProjectileManager& projectileManager) {}

    virtual void Update(float dt);
    virtual void Render(SDL_Renderer* renderer);
    virtual void RenderDebug(SDL_Renderer* renderer);

protected: // things the derived projectiles can access
    Vec2f dir_;
    SDL_Rect collider_rect_;
    Damage damage_;
    float movespeed_;
    float lifetime_;
    bool rotate_ = false;
    float angle_ = 0.0f; // angle in degrees
    float rotationspeed_ = 0.0f;
    SDL_Rect rect_;
    SDL_Texture* texture_; // texture to use for rendering, particle does not have ownership

    ResourceManagerPtr resource_manager_;
    ParticleManagerPtr particle_manager_;
    ParticleEmitterManagerPtr particle_emitter_manager_;

};

#endif