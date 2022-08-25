#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include <SDL2/SDL.h>

#include "base_character.h"

#include "Damage.h"

class UiManager;
class ProjectileManager;
class Player;

class BaseEnemy : public BaseCharacter
{
public:
    BaseEnemy(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resource_manager,
        std::shared_ptr<ParticleManager> particle_manager,
        std::shared_ptr<ParticleEmitterManager> particle_emitter_manager,
        std::shared_ptr<UiManager> ui_manager,
        std::shared_ptr<ProjectileManager> projectile_manager,
        std::shared_ptr<Player> player);

    Damage const& damage() const { return damage_; }
    
    // derived enemies can add any AI functionality if they wish
    virtual void UpdateAI(float dt) {}
    void Update(float dt) override;

protected:
    std::shared_ptr<UiManager> ui_manager_;
    std::shared_ptr<ProjectileManager> projectile_manager_;
    std::shared_ptr<Player> player_;
    Damage damage_;
    
};

#endif