#ifndef FIREBALL_EXPLOSION_H_
#define FIREBALL_EXPLOSION_H_

#include "BaseProjectile.h"

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(const Vec2f& pos,
        std::shared_ptr<ResourceManager> resourceManager,
        std::shared_ptr<ParticleManager> particleManager);

    void create(ProjectileManager& projectileManager) override {}
    void destroy(ProjectileManager& projectileManager) override {}
    
    void render(SDL_Renderer* renderer) override;

private:
    float gasSpawnTime = 0.02f;
    float gasSpawnTimer = gasSpawnTime;

};

#endif