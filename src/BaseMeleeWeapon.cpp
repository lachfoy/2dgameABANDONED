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
    posX = damageable->posX + offsetX;
    posY = damageable->posY + offsetY;
    collider->upperBoundX = posX - (colliderRadius / 2);
    collider->upperBoundY = posY - (colliderRadius / 2);
    collider->lowerBoundX = posX + (colliderRadius / 2);
    collider->lowerBoundY = posY + (colliderRadius / 2);
}