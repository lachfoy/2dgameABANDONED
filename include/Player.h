#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "BaseObject.h"

class AABB;

class Player : public BaseObject
{
public:
    Player(float x, float y);
    ~Player();

    AABB* collider;

    void update(float dt);
    void render(SDL_Renderer* renderer);

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

    void doDamage(int damage);

private:
    enum
    {
        DEFAULT_W = 30,
        DEFAULT_H = 60,
        DEFAULT_COLLIDER_W = 50,
        DEFAULT_COLLIDER_H = 50,
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_IMMUNE_TIME = 1,
        DEFAULT_MOVE_SPEED = 200
    };

    int playerW;
    int playerH;
    int colliderW;
    int colliderH;
    int maxHealth;
    int health;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
    float moveSpeed;
};

#endif