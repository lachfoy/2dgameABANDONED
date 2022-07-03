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

    void doDamage(int damage);
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

private:
    enum
    {
        DEFAULT_MAX_HEALTH = 100,
        DEFAULT_PLAYER_WIDTH = 30,
        DEFAULT_PLAYER_HEIGHT = 60,
        DEFAULT_MOVE_SPEED = 200
    };

    int playerW;
    int playerH;
    int colliderW;
    int colliderH;
    int health;
    int maxHealth;
    float moveSpeed;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
};

#endif