#ifndef FIREBALL_H
#define FIREBALL_H

#include "BaseProjectile.h"

class ProjectileManager;

class Fireball : public BaseProjectile
{
public:
    inline Fireball(ProjectileManager* projectileManager, float x, float y, int velX, int velY);
        
    inline ~Fireball();

    //inline void update(float dt); // base class handles updating
    inline void render(SDL_Renderer* renderer) override;

private:
    ProjectileManager* projectileManager; // needs reference to projectile manager
};

// when the fireball gets removed it spawns a new projectile. How tf I do this I do not know.
class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(float x, float y)
        : BaseProjectile(x, y, velX = 0, velY = 0)
    {
        colliderRadius = 38;
        lifeTime = 0.2f;
        damage = 23;
    }

    ~FireballExplosion() {}

    inline void render(SDL_Renderer* renderer) override;
};

#include "ProjectileManager.h"

Fireball::Fireball(ProjectileManager* projectileManager, float x, float y, int velX, int velY)
    : BaseProjectile(x, y, velX, velY)
{   
    this->projectileManager = projectileManager;
    colliderRadius = 24;
    moveSpeed = 220.0f;
    damage = 11;
    lifeTime = 1.6f;
}

Fireball::~Fireball()
{
    // Fireball should spawn a 'FireballExplosion' when it is destroyed
    projectileManager->addProjectile(new FireballExplosion(pos.x, pos.y));
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 12;
    debug_point_pos.h = 12;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xfc, 0x90, 0x03, 0xff); // #fc9003 fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 26;
    debug_point_pos.h = 26;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xff, 0x6a, 0x0d, 0xff); // #ff6a0d more intense fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}

#endif