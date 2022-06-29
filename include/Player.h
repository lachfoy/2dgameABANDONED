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
    
    void update(float dt);
    void render(SDL_Renderer* renderer);

private:
    int playerW;
    int playerH;
    int colliderW;
    int colliderH;
    float moveSpeed;
};

#endif