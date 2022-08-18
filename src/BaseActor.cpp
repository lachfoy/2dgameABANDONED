#include "BaseActor.h"

#include "ResourceManager.h"
#include "ParticleManager.h"

BaseActor::BaseActor(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager)
    : BaseObject(pos)
{
    this->m_resourceManager = resourceManager;
    this->particleManager = particleManager;
    collider = AABB2i(pos.x, pos.y, colliderW, colliderH);
    resistance = {0};
}

void BaseActor::takeDamage(const Damage& damage)
{
    if(!isImmune)
    {
        // set status
        if (damage.setBurning) isOnFire = true;

        // take damage
        int damageTaken = resistance.damageAfterRestistance(damage);
        health -= damageTaken;
        printf("%s took %i damage\n", name.c_str(), damageTaken);
        printf("%s has %i/%i HP\n", name.c_str(), health, maxHealth);
        isBeingHurt = true;
    }
}

// instead we should take in an origin pos, then do the velocity calculation.\
    we should also use some kind of calculation based on a "mass" attribute
void BaseActor::push(const Vec2f& pushDir, float pushMoveSpeed)
{
    if (!isBeingPushed)
    {
        this->pushDir.x = pushDir.x;
        this->pushDir.y = pushDir.y;
        this->pushMoveSpeed = pushMoveSpeed;
        isBeingPushed = true;
    }
}

void BaseActor::updatePush(float dt)
{
    // push timer
    if (isBeingPushed)
    {
        if (pushTimer > 0.0f)
        {
            dir.x = pushDir.x;
            dir.y = pushDir.y;
            moveSpeed = pushMoveSpeed;
            pushTimer -= dt;
        }
        else
        {
            // reset back to normal
            isBeingPushed = false;
            moveSpeed = startingMoveSpeed;
            pushTimer = pushTime;
        }
    }
}

void BaseActor::updateHurt(float dt)
{
    // hurt timer
    if (isBeingHurt)
    {
        if (hurtTimer > 0.0f)
        {
            hurtTimer -= dt;
        }
        else
        {
            hurtTimer = hurtCooldown; // reset to the starting value
            isBeingHurt = false;
        }
    }
}

void BaseActor::updateFire(float dt)
{
    // on fire timer
    if (canBeSetOnFire)
    {
        if (isOnFire) // they stay on fire not forever :)
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

                if (smokeParticleSpawnTimer > 0.0f) smokeParticleSpawnTimer -= dt;
                else
                {
                    // spawn a particle at the old position
                    printf("added smoke particle\n");
                    particleManager->addSmokeParticle({ pos.x, pos.y - (height / 2) });
                    smokeParticleSpawnTimer = smokeParticleSpawnTime; // reset timer
                }
            }
            else
            {
                isOnFire = false;
                fireTimer = fireTime;
            }
        }
    }
}

void BaseActor::updatePosition(float dt)
{
    // update facing direction
    if (dir.x > 0.0f)
        facingDirection = FACING_RIGHT;
    else if (dir.x < 0.0f)
        facingDirection = FACING_LEFT;

    // update the internal position
    pos.x += dir.x * moveSpeed * dt;
    pos.y += dir.y * (moveSpeed * 0.7f) * dt; // moving in the Y direction is a bit slower

    // reset velocity
    dir.x = 0.0f;
    dir.y = 0.0f;

    // move the collider as well
    // note: origin for NPCs/players is always bottom center
    collider.minX = (int)pos.x - (colliderW / 2);
    collider.minY = (int)pos.y - (colliderH / 2) - (height / 2);
    collider.maxX = (int)pos.x + (colliderW / 2);
    collider.maxY = (int)pos.y + (colliderH / 2) - (height / 2);
}

void BaseActor::renderShadow(SDL_Renderer* renderer)
{
    // draw the origin position representing the actual x and y positions
    SDL_Rect shadow_rect;
    const int max_width = 60; // set a max width for damageable objects, scale the shadow rect by a % of the width to the max width
    const int shadow_default_width = 60;
    const int shadow_default_height = 24;
    shadow_rect.w = (int)(shadow_default_width * (width / (float)max_width));
    shadow_rect.h = (int)(shadow_default_height * (width / (float)max_width));
    shadow_rect.x = (int)pos.x - (shadow_rect.w / 2);
    shadow_rect.y = (int)pos.y - (shadow_rect.h / 2);

    // draw texture
    SDL_RenderCopy(renderer, m_resourceManager->getTexture("ShadowTexture"), NULL, &shadow_rect);
}

void BaseActor::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider.debugRender(renderer);
}

