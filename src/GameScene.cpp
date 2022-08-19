#include "GameScene.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "particle_manager.h"

#define DEBUG_DRAW 1

GameScene::GameScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    resource_manager_->loadGameResources();

    ui_manager_ = std::make_shared<UiManager>(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);
    particle_manager_ = std::make_shared<ParticleManager>(resource_manager_);
    m_projectileManager = std::make_shared<ProjectileManager>(resource_manager_, particle_manager_);

    particle_emitter = std::make_unique<ParticleEmitter>(resource_manager_->getTexture("FireParticleTexture"),
        0.2f,
        10.0f,
        20.0f,
        30,
        Vec2f(500.0f, 300.0f),
        Vec2f(0.0f, 0.0f), // not used
        true,
        100.0f,
        300.0f,
        0.0f, // not used
        particle_manager_);

    const Vec2f playerPos = { 100.0f, 200.0f };
    m_player = std::make_shared<Player>(playerPos, resource_manager_, ui_manager_, m_projectileManager);
    
    m_enemyManager = std::make_shared<EnemyManager>(resource_manager_, particle_manager_, ui_manager_, m_projectileManager, m_player);
    // m_enemyManager->addSkeleton({ 400.0f, 300.0f });
    // m_enemyManager->addSkeleton({ 600.0f, 400.0f });
    // m_enemyManager->addSkeleton({ 500.0f, 500.0f });
    // m_enemyManager->addSkeleton({ 300.0f, 400.0f });
    // m_enemyManager->addSkeleton({ 700.0f, 200.0f });
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
    particle_emitter->Update(dt); // test

    // handle input
    m_player->handleInput(*m_inputManager);

    // update game objects
    m_player->update(dt);
    m_enemyManager->updateEnemies(dt);
    m_projectileManager->updateProjectiles(dt);
    particle_manager_->UpdateParticles(dt);

    // collision resolution
    m_enemyManager->resolvePlayerProjectileCollisions(m_projectileManager->player_projectiles());
    m_player->resolveEnemyCollisions(m_enemyManager->getEnemies());

    // update ui objects
    ui_manager_->updateUiObjects(dt);

    // remove unused objects
    m_enemyManager->removeUnusedEnemies();
    m_projectileManager->removeUnusedProjectiles();
    ui_manager_->removeUnusedUiObjects();
}

void GameScene::render(SDL_Renderer* renderer)
{
    // render game objects
    m_enemyManager->renderEnemies(renderer);
    m_player->renderShadow(renderer);
    m_player->render(renderer);
    particle_manager_->RenderParticles(renderer);
    m_projectileManager->renderProjectiles(renderer);

    // render ui objects
    ui_manager_->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        m_enemyManager->renderDebug(renderer);
        m_player->renderDebug(renderer);
        m_projectileManager->renderDebug(renderer);
    }
}





