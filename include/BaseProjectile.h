#ifndef BASEPROJECTILE_H
#define BASEPROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"
#include "Damage.h"

class ProjectileManager;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager);
    virtual ~BaseProjectile(); // must be virtual so that derived projectiles have the option of adding more functionality to destruction

    AABB getCollider() const { return *collider; }
    Damage getDamage() const { return damage; }
    
    virtual void updatePosition(float dt); // derived projectiles can override update ONLY if they need to

protected: // things the derived projectiles can change
    int velX; // normalized x velocity
    int velY; // normalized y velocity
    ProjectileManager* projectileManager;
    AABB* collider;
    Damage damage;
    float moveSpeed;
    int colliderRadius; // assume all projectiles have uniform width and height even though they are actually rectangles
    float lifeTime;
};

#endif