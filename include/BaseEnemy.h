#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <SDL2/SDL.h>

#include "BaseDamageable.h"

#include "Damage.h"

class UiManager;
class ProjectileManager;
class Player;

class BaseEnemy : public BaseDamageable
{
public:
    BaseEnemy(float x, float y, ResourceManager* resourceManager, ParticleManager* particleManager, UiManager* uiManager, ProjectileManager* projectileManager, Player* player);
    virtual ~BaseEnemy() {} // derived enemies can add functionality to their destructors

    Damage getDamage() const { return damage; }
    
    // derived enemies can add any AI functionality if they wish
    virtual void updateAI(float dt) = 0;

protected:
    UiManager* m_uiManager;
    ProjectileManager* projectileManager;
    Player* player;
    Damage damage;
    
};

#endif