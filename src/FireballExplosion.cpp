#include "FireballExplosion.h"

#include "ParticleManager.h"

FireballExplosion::FireballExplosion(float x, float y, SDL_Texture* texture, ParticleManager* particleManager)
    : BaseProjectile(x, y, 0, 0, texture, particleManager)
{
    name = "FireballExplosion";
    colliderW = 200;
    colliderH = 200;
    damage = {0};
    damage = { .fire = 43, .setBurning = true };
    lifeTime = 0.3f;
    removeOnCollision = false;
    onlyDamageOnce = true;
}

void FireballExplosion::spawnParticles(float dt)
{
    float gasVelX = 0.5f;
    float gasVelY = 0.5f;
    if (gasSpawnTimer > 0.0f) gasSpawnTimer -= dt;
    else
    {
        // spawn a particle at the old position
        particleManager->addFireballExplosionParticle(posX, posY, gasVelX, gasVelY);
        gasSpawnTimer = gasSpawnTime; // reset timer
    }
}

void FireballExplosion::render(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect fireball_explosion_rect;
    fireball_explosion_rect.w = 200;
    fireball_explosion_rect.h = 200;
    fireball_explosion_rect.x = (int)posX - (fireball_explosion_rect.w / 2);
    fireball_explosion_rect.y = (int)posY - (fireball_explosion_rect.h / 2);

    SDL_RenderCopy(renderer, texture, NULL, &fireball_explosion_rect);

    // draw collider
    //collider.debugRender(renderer);
}