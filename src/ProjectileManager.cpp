#include "ProjectileManager.h"

#include "Fireball.h"
#include "FireballExplosion.h"
#include "Sword.h"
#include "BaseDamageable.h"
#include "SwordSlash.h"
#include "ResourceManager.h"

ProjectileManager::ProjectileManager(std::shared_ptr<ResourceManager> resourceManager, std::shared_ptr<ParticleManager> particleManager)
{
    m_resourceManager = resourceManager;
    this->particleManager = particleManager;
}

ProjectileManager::~ProjectileManager()
{
    // clear the projectiles vectors
    m_enemyProjectiles.clear();
    m_playerProjectiles.clear();
}

void ProjectileManager::addFireball(const Vec2f& pos, const Vec2f& dir)
{
    m_playerProjectiles.push_back(std::make_unique<Fireball>(pos, dir, m_resourceManager->getTexture("FireballTexture"), particleManager));
}

void ProjectileManager::addFireballExplosion(const Vec2f& pos)
{
    m_playerProjectiles.push_back(std::make_unique<FireballExplosion>(pos, m_resourceManager->getTexture("FireballExplosionTexture"), particleManager));
}

void ProjectileManager::addSword(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder)
{
    m_playerProjectiles.push_back(std::make_unique<Sword>(pos, offsetX, offsetY, m_resourceManager->getTexture("SwordTexture"), wielder));
}

void ProjectileManager::addSwordSlash(const Vec2f& pos, float offsetX, float offsetY, BaseDamageable* wielder)
{
    m_playerProjectiles.push_back(std::make_unique<SwordSlash>(pos, offsetX, offsetY, m_resourceManager->getTexture("SwordSlashTexture"), wielder));
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
            m_playerProjectiles.erase(m_playerProjectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileManager::renderProjectiles(SDL_Renderer* renderer)
{
    for (const auto& projectile : m_enemyProjectiles) projectile->render(renderer);
    for (const auto& projectile : m_playerProjectiles) projectile->render(renderer);
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