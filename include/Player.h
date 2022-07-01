#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "BaseObject.h"
#include "Point2f.h"
#include "AABB.h"

class Player : public BaseObject
{
public:
    Player();
    ~Player();

    AABB* collider;
    int health;
    int maxHealth;
    
    void update(float dt);
    void render(SDL_Renderer* renderer);

    void doDamage(int damage);

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
    float moveSpeed;
    bool damageable; // if not damageable then they are taking damage
    float immuneTimer;
    float immuneTime; // how many iframes (in seconds though)
};

#endif