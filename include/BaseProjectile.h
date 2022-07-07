#ifndef BASEPROJECTILE_H
#define BASEPROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"

class ProjectileManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager);
    virtual ~BaseProjectile(); // must be virtual so that derived projectiles have the option of adding more functionality to destruction

    inline AABB getCollider() const { return *collider; }
    inline int getDamage() const { return damage; }
    
    virtual void update(float dt); // derived projectiles can override update ONLY if they need to

private:
    enum // defaults
    {
        DEFAULT_LIFETIME = 1, // float
        DEFAULT_DAMAGE = 10,
        DEFAULT_MOVESPEED = 300, // float
        DEFAULT_COLLIDER_RADIUS = 10
    };

protected: // things the derived projectiles can change
    int velX; // normalized x velocity
    int velY; // normalized y velocity
    ProjectileManager* projectileManager;
    AABB* collider;
    int damage = DEFAULT_DAMAGE;
    float moveSpeed = (float)DEFAULT_MOVESPEED;
    int colliderRadius = DEFAULT_COLLIDER_RADIUS; // assume all projectiles have uniform width and height even though they are actually rectangles
    float lifeTime = (float)DEFAULT_LIFETIME;
};

#endif