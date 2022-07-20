#include "BaseDamageable.h"

BaseDamageable::BaseDamageable(float x, float y)
    : BaseObject(x, y)
{
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

void BaseDamageable::renderCollider(SDL_Renderer* renderer)
{
    // draw collider
    collider.debugRender(renderer);
}

