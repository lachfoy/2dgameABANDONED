#ifndef FIREBALL_H_
#define FIREBALL_H_

#include "BaseProjectile.h"

class Fireball : public BaseProjectile
{
public:
    Fireball(const Vec2f& pos,
        const Vec2f& dir,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager);

    void OnDestroy(ProjectileManager& projectileManager) override;

    void Render(SDL_Renderer* renderer) override;

private:
    float trailSpawnTime = 0.02f;
    float trailSpawnTimer = trailSpawnTime;

};

#endif