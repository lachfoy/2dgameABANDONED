#include "BaseMeleeWeapon.h"

#include "BaseActor.h"

BaseMeleeWeapon::BaseMeleeWeapon(const Vec2f& pos, float offsetX, float offsetY, SDL_Texture* texture, BaseActor* actor)
     : BaseProjectile(pos, { 0.0f, 0.0f }, texture, nullptr)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    this->actor = actor;

    removeOnCollision = false;
    onlyDamageOnce = true;
}

void BaseMeleeWeapon::updatePosition(float dt)
{
    // follow the position of the actor + an offset
    pos.x = actor->pos.x + offsetX;
    pos.y = actor->pos.y + offsetY;

    if (rotate)
    {
        if (angle >= 360)
            angle = 0.0f;
        else
            angle += rotationSpeed;
    }

    // flip based on actor's facing direction
    flip = !actor->facingRight();

    // move the collider as well
    collider.minX = (int)pos.x - (colliderW / 2);
    collider.minY = (int)pos.y - (colliderH / 2);
    collider.maxX = (int)pos.x + (colliderW / 2);
    collider.maxY = (int)pos.y + (colliderH / 2);
}