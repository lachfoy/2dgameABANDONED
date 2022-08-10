#include "BaseMeleeWeapon.h"

#include "BaseDamageable.h"

BaseMeleeWeapon::BaseMeleeWeapon(float x, float y, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder)
     : BaseProjectile(x, y, 0, 0, texture) // no texture for now
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    this->wielder = wielder;

    removeOnCollision = false;
    onlyDamageOnce = true;
}

void BaseMeleeWeapon::updatePosition(float dt)
{
    // follow the position of the wielder + an offset
    posX = wielder->posX + offsetX;
    posY = wielder->posY + offsetY;

    if (rotate)
    {
        if (angle >= 360)
            angle = 0.0f;
        else
            angle += rotationSpeed;
    }

    // flip based on wielder's facing direction
    flip = !wielder->facingRight();

    // move the collider as well
    collider.upperBoundX = posX - (colliderW / 2);
    collider.upperBoundY = posY - (colliderH / 2);
    collider.lowerBoundX = posX + (colliderW / 2);
    collider.lowerBoundY = posY + (colliderH / 2);
}