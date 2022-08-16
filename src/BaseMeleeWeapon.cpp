#include "BaseMeleeWeapon.h"

#include "BaseDamageable.h"

BaseMeleeWeapon::BaseMeleeWeapon(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseDamageable* wielder)
     : BaseProjectile(pos, { 0.0f, 0.0f }, texture, nullptr)
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
    pos.x = wielder->pos.x + offsetX;
    pos.y = wielder->pos.y + offsetY;

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
    collider.minX = (int)pos.x - (colliderW / 2);
    collider.minY = (int)pos.y - (colliderH / 2);
    collider.maxX = (int)pos.x + (colliderW / 2);
    collider.maxY = (int)pos.y + (colliderH / 2);
}