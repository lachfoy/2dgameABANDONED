#ifndef PARTICLE_SPAWNER_H
#define PARTICLE_SPAWNER_H

#include <memory>

class ParticleManager;

class ParticleSpawner
{
public:
    ParticleSpawner(float tickTime, std::shared_ptr<ParticleManager> particleManager)
    {}
    
    ~ParticleSpawner()
    {}

    void update(float dt)
    {}

private:
    std::shared_ptr<ParticleManager> m_particleManager;
    float tickTime;

};

#endif