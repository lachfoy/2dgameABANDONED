#ifndef PARTICLE_SPAWNER_H
#define PARTICLE_SPAWNER_H

#include <memory>
#include <string>
#include <cstdlib> // rand
#include <cmath> // sin cos

#include "Vec2f.h"
#include "ParticleManager.h"

// this isn't really that great but I don't have a better way of specifying the type
enum ParticleType
{
    PARTICLE_FIRE,
    PARTICLE_SMOKE,
    PARTICLE_EXPLOSION
};

class ParticleSpawner
{
public:
    inline ParticleSpawner(ParticleType particleType,
        float spawnInterval,
        int numParticles,
        const Vec2f& origin,
        const Vec2f& particleDir, // only used if randomDir = false
        bool randomDir,
        float particleMoveSpeedMin,
        float particleMoveSpeedMax,
        float gravity, // unused
        std::shared_ptr<ParticleManager> particleManager)
    {
        m_particleType = particleType;
        m_spawnInterval = spawnInterval;
        m_numParticles = numParticles;
        m_origin = origin;
        m_particleDir = particleDir;
        m_randomDir = randomDir;
        m_particleMoveSpeedMin = particleMoveSpeedMin;
        m_particleMoveSpeedMax = particleMoveSpeedMax;
        m_gravity = gravity;
        m_particleManager = particleManager;
    }

    ~ParticleSpawner()
    {

    }

    void update(float dt)
    {
        if (m_spawnTimer > 0.0f) m_spawnTimer -= dt;
        else
        {
            for (int i = 0; i < m_numParticles; i++)
            {
                if (m_randomDir) // pick a random direction
                {
                    const float randomGrad = 2.0f * M_PI * ((rand() % 100 + 1) / 100.0f); // random gradian
                    m_particleDir = Vec2f(cosf(randomGrad), sinf(randomGrad));
                }

                const float randomMoveSpeed = rand() % (int)(m_particleMoveSpeedMax - m_particleMoveSpeedMin + 1) + m_particleMoveSpeedMin;
                m_particleManager->addFireballParticle(m_origin, m_particleDir, randomMoveSpeed);

            }
            m_spawnTimer = m_spawnInterval;
        }
        
        
    }

private:
    ParticleType m_particleType;
    float m_spawnInterval;
    float m_spawnTimer;
    int m_numParticles;
    Vec2f m_origin;
    Vec2f m_particleDir;
    bool m_randomDir;
    float m_particleMoveSpeedMin;
    float m_particleMoveSpeedMax;
    float m_gravity;
    std::shared_ptr<ParticleManager> m_particleManager;
    
    

};

#endif