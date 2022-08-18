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
    BaseEnemy(const Vec2f& pos,
        std::shared_ptr<ResourceManager> ResourceManager,
        std::shared_ptr<ParticleManager> particleManager,
        std::shared_ptr<UiManager> uiManager,
        std::shared_ptr<ProjectileManager> projectileManager,
        std::shared_ptr<Player> player);
    virtual ~BaseEnemy() {} // derived enemies can add functionality to their destructors

    Damage getDamage() const { return damage; }
    
    // derived enemies can add any AI functionality if they wish
    virtual void updateAI(float dt) = 0;

protected:
    std::shared_ptr<UiManager> m_uiManager;
    std::shared_ptr<ProjectileManager> projectileManager;
    std::shared_ptr<Player> player;
    Damage damage;
    
};

#endif