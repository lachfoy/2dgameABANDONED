#include "BaseDamageable.h"

#include "ResourceManager.h"
#include "ParticleManager.h"

BaseDamageable::BaseDamageable(float x, float y, ResourceManager* resourceManager, ParticleManager* particleManager)
    : BaseObject(x, y)
{
    this->resourceManager = resourceManager;
    this->particleManager = particleManager;
    collider = AABB(posX, posY, colliderW, colliderH);
    resistance = {0};
}

void BaseDamageable::takeDamage(const Damage& damage)
{
    if(damageable)
    {
        // set status
        if (damage.setBurning) onFire = true;

        // take damage
        int damageTaken = resistance.damageAfterRestistance(damage);
        health -= damageTaken;
        printf("%s took %i damage\n", name.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name.c_str(), health, maxHealth);
        damageable = false; // give iframes
    }
}

void BaseDamageable::updateBurning(float dt)
{
    if (canBeSetOnFire)
    {
        if (onFire) // they stay on fire not forever :)
        {
            if (fireTimer > 0.0f)
            {
                fireTimer -= dt;

                if (fireTickTimer > 0.0f) fireTickTimer -= dt;
                else
                {
                    takeDamage(statusBurning);
                    fireTickTimer = fireTickTime; // reset to the starting value
                }

                if (smokeParticleSpawnTimer > 0.0f) smokeParticleSpawnTime -= dt;
                else
                {
                    // spawn a particle at the old position
                    particleManager->addSmokeParticle(posX, posY);
                    smokeParticleSpawnTimer = smokeParticleSpawnTime; // reset timer
                }
            }
            else
            {
                onFire = false;
                fireTimer = fireTime;
            }
        }
    }
}

// instead we should take in an origin pos, then do the velocity calculation.\
    we should also use some kind of calculation based on a "mass" attribute
void BaseDamageable::push(float pushVelX, float pushVelY, float pushMoveSpeed)
{
    if (!beingPushed)
    {
        this->pushVelX = pushVelX;
        this->pushVelY = pushVelY;
        this->pushMoveSpeed = pushMoveSpeed;
        beingPushed = true;
    }
}

void BaseDamageable::updatePush(float dt)
{
    if (beingPushed)
    {
        if (pushTimer > 0.0f)
        {
            velX = pushVelX;
            velY = pushVelY;
            moveSpeed = pushMoveSpeed;
            pushTimer -= dt;
        }
        else
        {
            // reset back to normal
            beingPushed = false;
            moveSpeed = startingMoveSpeed;
            pushTimer = pushTime;
        }
    }
}

void BaseDamageable::updateImmuneTimer(float dt)
{
    if (health <= 0) { printf("%s is dead\n", name.c_str()); removable = true; }
    else
    {
        // set up iframes
        if (!damageable) immuneTimer -= dt;
        if (immuneTimer <= 0.0f)
        {
            immuneTimer = immuneTime; // reset to the starting value
            damageable = true;
        }
    }
}

void BaseDamageable::updatePosition(float dt)
{
    // update facing direction
    if (velX > 0.0f)
        facingDirection = FACING_RIGHT;
    else if (velX < 0.0f)
        facingDirection = FACING_LEFT;

    // update the internal position
    posX += velX * moveSpeed * dt;
    posY += velY * (moveSpeed * 0.7f) * dt; // moving in the Y direction is a bit slower

    // reset velocity
    velX = 0.0f;
    velY = 0.0f;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider.upperBoundX = posX - (colliderW / 2);
    collider.upperBoundY = posY - (colliderH / 2) - (height / 2);
    collider.lowerBoundX = posX + (colliderW / 2);
    collider.lowerBoundY = posY + (colliderH / 2) - (height / 2);
}

void BaseDamageable::renderShadow(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect shadow_rect;
    const int max_width = 60; // set a max width for damageable objects, scale the shadow rect by a % of the width to the max width
    const int shadow_default_width = 60;
    const int shadow_default_height = 24;
    shadow_rect.w = (int)(shadow_default_width * (width / (float)max_width));
    shadow_rect.h = (int)(shadow_default_height * (width / (float)max_width));
    shadow_rect.x = (int)posX - (shadow_rect.w / 2);
    shadow_rect.y = (int)posY - (shadow_rect.h / 2);

    // draw texture
    SDL_RenderCopy(renderer, resourceManager->getTexture("ShadowTexture"), NULL, &shadow_rect);
}

void BaseDamageable::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider.debugRender(renderer);
}

