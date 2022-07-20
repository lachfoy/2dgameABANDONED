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
    BaseProjectile(float x, float y, int velX, int velY, SDL_Texture* texture = nullptr);
    virtual ~BaseProjectile() {}

    bool removeOnCollision;
    bool onlyDamageOnce;
    bool hasDealtDamage = false;

    AABB const& getCollider() const { return collider; }
    Damage const& getDamage() const { return damage; }
    int getVelX() const { return velX; }
    int getVelY() const { return velY; }
    
    void updateLifetime(float dt);
    virtual void destroy(ProjectileManager& projectileManager) = 0;
    virtual void updatePosition(float dt); // derived projectiles can override update ONLY if they need to

    // debug
    void renderCollider(SDL_Renderer* renderer);

protected: // things the derived projectiles can change
    int velX; // normalized x velocity
    int velY; // normalized y velocity
    AABB collider;
    int colliderW;
    int colliderH;
    Damage damage;
    float moveSpeed;
    float lifeTime;
    SDL_Texture* texture; // texture to use for rendering, projectile does not have ownership

};

#endif