#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "Sword.h"
#include "BaseDamageable.h"
#include "SwordSlash.h"
#include "ResourceManager.h"

ProjectileManager::ProjectileManager(ResourceManager* resourceManager, ParticleManager* particleManager)
{
    this->m_resourceManager = resourceManager; // ptr to resource manager, used when creating projectiles to give them the appropriate textures
    this->particleManager = particleManager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors and delete the pointers
    // enemy projectiles
    for (const auto& projectile : m_enemyProjectiles) delete projectile;
    m_enemyProjectiles.clear();

    // player projectiles
    for (const auto& projectile : m_playerProjectiles) delete projectile;
    m_playerProjectiles.clear();
}

void ProjectileManager::addFireball(const Vec2f& pos, const Vec2f& dir)
{
    m_playerProjectiles.push_back(new Fireball(pos, dir, m_resourceManager->getTexture("FireballTexture"), particleManager));
}

void ProjectileManager::addFireballExplosion(const Vec2f& pos)
{
    m_playerProjectiles.push_back(new FireballExplosion(pos, m_resourceManager->getTexture("FireballExplosionTexture"), particleManager));
}

void ProjectileManager::addSword(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder)
{
    m_playerProjectiles.push_back(new Sword(pos, offsetX, offsetY, m_resourceManager->getTexture("SwordTexture"), wielder));
}

void ProjectileManager::addSwordSlash(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder)
{
    m_playerProjectiles.push_back(new SwordSlash(pos, offsetX, offsetY, m_resourceManager->getTexture("SwordSlashTexture"), wielder));
}

void ProjectileManager::updateProjectiles(float dt)
{
    // enemy projectiles
    for (const auto& projectile : m_enemyProjectiles)
    {
        projectile->updatePosition(dt);
        projectile->spawnParticles(dt);
        projectile->updateLifetime(dt);
    }

    // player projectiles
    for (const auto& projectile : m_playerProjectiles)
    {
        projectile->updatePosition(dt);
        projectile->spawnParticles(dt);
        projectile->updateLifetime(dt);
    }
}

void ProjectileManager::removeUnusedProjectiles()
{
    // enemy projectiles
    for (int i = 0; i < m_enemyProjectiles.size(); i++)
    {
        if (m_enemyProjectiles[i]->removable)
        {
            m_enemyProjectiles[i]->destroy(*this);
            delete m_enemyProjectiles[i];
            m_enemyProjectiles.erase(m_enemyProjectiles.begin() + i);
            i--;
        }
    }

    // player projectiles
    for (int i = 0; i < m_playerProjectiles.size(); i++)
    {
        if (m_playerProjectiles[i]->removable)
        {
            m_playerProjectiles[i]->destroy(*this);
            delete m_playerProjectiles[i];
            m_playerProjectiles.erase(m_playerProjectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : m_enemyProjectiles)
    {
        projectile->render(renderer);
    }

    // player projectiles
    for (const auto& projectile : m_playerProjectiles)
    {
        projectile->render(renderer);
    }
}

void ProjectileManager::renderDebug(SDL_Renderer* renderer)
{
    // enemy projectiles
    for (const auto& projectile : m_enemyProjectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }

    // player projectiles
    for (const auto& projectile : m_playerProjectiles)
    {
        projectile->renderCollider(renderer);
        projectile->renderOrigin(renderer);
    }
}