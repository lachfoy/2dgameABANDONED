#ifndef BASEPROJECTILE_H
#define BASEPROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class ProjectileManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(float x, float y, int velX, int velY);
    ~BaseProjectile(); // must be virtual so that derived projectiles have the option of adding more functionality to destruction

    inline AABB getCollider() const { return *collider; }
    inline int getDamage() const { return damage; }
    
    // if derived projectiles need to access the manager onDestroy then they can implement this.
    virtual void onDestroy(ProjectileManager& projectileManager) = 0;

    virtual void update(float dt); // derived projectiles can override update ONLY if they need to
    virtual void render(SDL_Renderer* renderer) = 0; // derived projectiles MUST provide an implementation for renderering

private:
    enum // defaults
    {
        DEFAULT_LIFETIME = 1, // float
        DEFAULT_DAMAGE = 10,
        DEFAULT_MOVESPEED = 300, // float
        DEFAULT_COLLIDER_RADIUS = 10
    };

protected: // things the derived projectiles can change
    AABB* collider;
    int damage; // TODO: pack damage information into a struct so i can have different damage types?
    float moveSpeed;
    int colliderRadius; // assume all projectiles have uniform width and height even though they are actually rectangles
    float lifeTime;
};

#endif