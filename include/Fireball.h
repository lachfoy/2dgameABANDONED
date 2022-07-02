#ifndef FIREBALL_H
#define FIREBALL_H

#include "Projectile.h"
#include "ProjectileManager.h"

class Fireball : public Projectile
{
public:
    inline Fireball(ProjectileManager* projectileManager, float x, float y, int velX, int velY);
        
    inline ~Fireball();

    //inline void update(float dt); // base class handles updating
    inline void render(SDL_Renderer* renderer);

private:
    ProjectileManager* projectileManager; // needs reference to projectile manager
};

// when the fireball gets removed it spawns a new projectile. How tf I do this I do not know.
class FireballExplosion : public Projectile
{
public:
    FireballExplosion(float x, float y)
        : Projectile(x, y, velX = 0, velY = 0)
    {
        colliderRadius = 32;
        lifeTime = 0.2f;
        damage = 19;
    }

    ~FireballExplosion() { printf("Deleted Fireball Explosion\n"); }

    inline void render(SDL_Renderer* renderer);
};

Fireball::Fireball(ProjectileManager* projectileManager, float x, float y, int velX, int velY)
    : Projectile(x, y, velX, velY)
{   
    this->projectileManager = projectileManager;
    colliderRadius = 24;
    moveSpeed = 300.0f;
    damage = 11;
    lifeTime = 1.6f;
}

Fireball::~Fireball()
{
    // Fireball should spawn a 'FireballExplosion' on removal.
    printf("Deleted Fireball\n");
    projectileManager->addProjectile(new FireballExplosion(pos.x, pos.y));
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect debug_point_pos;
    debug_point_pos.w = 14;
    debug_point_pos.h = 14;
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
    debug_point_pos.w = 22;
    debug_point_pos.h = 22;
    debug_point_pos.x = (int)pos.x - (debug_point_pos.w / 2);
    debug_point_pos.y = (int)pos.y - (debug_point_pos.h / 2);
    SDL_SetRenderDrawColor(renderer, 0xff, 0x6a, 0x0d, 0xff); // #ff6a0d more intense fire orange
    SDL_RenderFillRect(renderer, &debug_point_pos);

    // draw collider ig
    collider->debugRender(renderer);
}

#endif