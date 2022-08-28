#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include <SDL2/SDL.h>

#include "base_character.h"

#include "Damage.h"

class UiManager;
class ProjectileManager;
class Player;

typedef std::shared_ptr<ProjectileManager> ProjectileManagerPtr;
typedef std::shared_ptr<Player> PlayerPtr;

class BaseEnemy : public BaseCharacter
{
public:
    BaseEnemy(const Vec2f& pos,
        ResourceManagerPtr resource_manager,
        ParticleEmitterManagerPtr particle_emitter_manager,
        UiManager& ui_manager,
        ProjectileManagerPtr projectile_manager,
        PlayerPtr player);

    Damage const& damage() const { return damage_; }

    void Update(float dt) override;

protected:
    // derived enemies can add any AI functionality if they wish
    virtual void UpdateAI(float dt) {}

    ProjectileManagerPtr projectile_manager_;
    PlayerPtr player_;
    Damage damage_;
    
};

#endif