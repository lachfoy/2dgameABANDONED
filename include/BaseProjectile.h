#ifndef BASEPROJECTILE_H
#define BASEPROJECTILE_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "AABB.h"
#include "Damage.h"

class ProjectileManager;
class BaseDamageable;

class BaseProjectile : public BaseObject
{
public:
    BaseProjectile(float x, float y, int velX, int velY, ProjectileManager* projectileManager, BaseDamageable* damageable);

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    AABB const& getCollider() const { return collider; }
    Damage const& getDamage() const { return damage; }
    
    void updateLifetime(float dt);
    virtual void destroy() { removable = true; };
    virtual void updatePosition(float dt); // derived projectiles can override update ONLY if they need to

protected: // things the derived projectiles can change
    ProjectileManager* projectileManager;
    BaseDamageable* damageable;
    int velX; // normalized x velocity
    int velY; // normalized y velocity
    AABB collider;
    int colliderW;
    int colliderH;
    Damage damage;
    float moveSpeed;
    float lifeTime;

};

#endif