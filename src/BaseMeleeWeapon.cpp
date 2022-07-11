#include "BaseMeleeWeapon.h"

#include "BaseDamageable.h"

BaseMeleeWeapon::BaseMeleeWeapon(float x, float y, float offsetX, float offsetY, BaseDamageable* damageable)
     : BaseProjectile(x, y, 0, 0, nullptr, damageable)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

void BaseMeleeWeapon::updatePosition(float dt)
{
    // follow the position of the wielder + an offset
    posX = damageable->posX + offsetX;
    posY = damageable->posY + offsetY;

    // move the collider as well
    collider->upperBoundX = posX - (colliderW / 2);
    collider->upperBoundY = posY - (colliderH / 2);
    collider->lowerBoundX = posX + (colliderW / 2);
    collider->lowerBoundY = posY + (colliderH / 2);
}