#ifndef FIREBALLEXPLOSION_H
#define FIREBALLEXPLOSION_H

#include "BaseProjectile.h"

class FireballExplosion : public BaseProjectile
{
public:
    FireballExplosion(const Vec2f& pos, SDL_Texture* texture, ParticleManager* particleManager);

    void destroy(ProjectileManager& projectileManager) override {}
    void spawnParticles(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    float gasSpawnTime = 0.02f;
    float gasSpawnTimer = gasSpawnTime;

};

#endif