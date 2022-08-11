#include "Fireball.h"

#include "ProjectileManager.h"
#include "ParticleManager.h"

Fireball::Fireball(float x, float y, float velX, float velY, SDL_Texture* texture, ParticleManager* particleManager)
    : BaseProjectile(x, y, velX, velY, texture, particleManager)
{
    name = "Fireball";
    colliderW = 24;
    colliderH = 24;
    moveSpeed = 420.0f;
    damage = {0};
    damage = { .fire = 11 };
    lifeTime = 0.8f;
    removeOnCollision = true;
    onlyDamageOnce = true;
    rotate = true;
    rotationSpeed = 5.0f;
}

void Fireball::destroy(ProjectileManager& projectileManager)
{
    // when destroyed, create an explosion
    projectileManager.addFireballExplosion(posX, posY);
}

// this should be redone in a better way... im just not sure how
void Fireball::updatePosition(float dt)
{
    if (trailSpawnTimer > 0.0f) trailSpawnTimer -= dt;
    else
    {
        // spawn a particle at the old position
        particleManager->addFireballParticle(posX, posY);
        trailSpawnTimer = trailSpawnTime; // reset timer
    }

    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * moveSpeed * dt;

    if (rotate)
    {
        if (angle >= 360)
            angle = 0.0f;
        else
            angle += rotationSpeed;
    }

    // move the collider as well
    collider.upperBoundX = posX - (colliderW / 2);
    collider.upperBoundY = posY - (colliderH / 2);
    collider.lowerBoundX = posX + (colliderW / 2);
    collider.lowerBoundY = posY + (colliderH / 2);
}

void Fireball::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_rect;
    fireball_rect.w = 24;
    fireball_rect.h = 24;
    fireball_rect.x = (int)posX - (fireball_rect.w / 2);
    fireball_rect.y = (int)posY - (fireball_rect.h / 2);

    // draw the fireball
    SDL_RenderCopyEx(renderer, texture, NULL, &fireball_rect, angle, NULL, {});

    // draw collider
    //collider.debugRender(renderer);
}