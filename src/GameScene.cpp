#include "GameScene.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "ParticleManager.h"

#define DEBUG_DRAW 1

GameScene::GameScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    m_resourceManager->loadGameResources();

    m_uiManager = std::make_shared<UiManager>(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
    m_particleManager = std::make_shared<ParticleManager>(m_resourceManager);
    m_projectileManager = std::make_shared<ProjectileManager>(m_resourceManager, m_particleManager);

    particleEmitter = std::make_unique<ParticleEmitter>(PARTICLE_FIRE,
        0.2f,
        30,
        Vec2f(500.0f, 300.0f),
        Vec2f(0.0f, 0.0f),
        true,
        100.0f,
        300.0f,
        0.0f,
        m_particleManager);

    const Vec2f playerPos = { 100.0f, 200.0f };
    m_player = std::make_shared<Player>(playerPos, m_resourceManager, m_uiManager, m_projectileManager);
    
    m_enemyManager = std::make_shared<EnemyManager>(m_resourceManager, m_particleManager, m_uiManager, m_projectileManager, m_player);
    m_enemyManager->addSkeleton({ 400.0f, 300.0f });
    m_enemyManager->addSkeleton({ 600.0f, 400.0f });
    m_enemyManager->addSkeleton({ 500.0f, 500.0f });
    m_enemyManager->addSkeleton({ 300.0f, 400.0f });
    m_enemyManager->addSkeleton({ 700.0f, 200.0f });
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
    particleEmitter->update(dt); // test

    // handle input
    m_player->handleInput(*m_inputManager);

    // update game objects
    m_player->update(dt);
    m_enemyManager->updateEnemies(dt);
    m_projectileManager->updateProjectiles(dt);
    m_particleManager->updateParticles(dt);

    // collision resolution
    m_enemyManager->resolvePlayerProjectileCollisions(m_projectileManager->getPlayerProjectiles());
    m_player->resolveEnemyCollisions(m_enemyManager->getEnemies());

    // update ui objects
    m_uiManager->updateUiObjects(dt);

    // remove unused objects
    m_enemyManager->removeUnusedEnemies();
    m_projectileManager->removeUnusedProjectiles();
    m_uiManager->removeUnusedUiObjects();
    m_particleManager->removeUnusedParticles();
}

void GameScene::render(SDL_Renderer* renderer)
{
    // render game objects
    m_enemyManager->renderEnemies(renderer);
    m_player->renderShadow(renderer);
    m_player->render(renderer);
    m_particleManager->renderParticles(renderer);
    m_projectileManager->renderProjectiles(renderer);

    // render ui objects
    m_uiManager->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        m_enemyManager->renderDebug(renderer);
        m_player->renderDebug(renderer);
        m_projectileManager->renderDebug(renderer);
    }
}





