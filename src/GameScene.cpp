#include "GameScene.h"

#include "player.h"
#include "projectile_manager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "particle_manager.h"
#include "particle_emitter_manager.h"
#include "debug_text_manager.h"

#define DEBUG_DRAW 1

GameScene::GameScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{
    resource_manager_->LoadGameTextures();
    resource_manager_->LoadSounds();

    ui_manager_ = std::make_shared<UiManager>(m_inputManager, resource_manager_, m_windowWidth, m_windowHeight);

    particle_manager_ = std::make_shared<ParticleManager>(resource_manager_);
    particle_emitter_manager_ = std::make_shared<ParticleEmitterManager>(particle_manager_);

    m_projectileManager = std::make_shared<ProjectileManager>(resource_manager_, particle_manager_, particle_emitter_manager_);

    const Vec2f playerPos = { 100.0f, 200.0f };
    m_player = std::make_shared<Player>(playerPos, resource_manager_, particle_emitter_manager_, *ui_manager_, m_projectileManager);
    
    debug_text_manager_ = std::make_shared<DebugTextManager>(resource_manager_->GetFont("debug_font"));

    m_enemyManager = std::make_shared<EnemyManager>(resource_manager_, particle_emitter_manager_, ui_manager_, m_projectileManager, m_player);
    // m_enemyManager->addSkeleton({ 400.0f, 300.0f });
    // m_enemyManager->addSkeleton({ 600.0f, 400.0f });
    // m_enemyManager->addSkeleton({ 500.0f, 500.0f });
    // m_enemyManager->addSkeleton({ 300.0f, 400.0f });
    m_enemyManager->addSkeleton({ 700.0f, 200.0f });
}

GameScene::~GameScene()
{
}

void GameScene::update(float dt)
{
    

    // handle input
    m_player->handleInput(*m_inputManager);

    // update game objects
    m_player->Update(dt);
    m_enemyManager->updateEnemies(dt);
    m_projectileManager->UpdateProjectiles(dt);
    particle_manager_->UpdateParticles(dt);
    particle_emitter_manager_->UpdateParticleEmitters(dt);

    // collision resolution
    m_enemyManager->resolvePlayerProjectileCollisions(m_projectileManager->player_projectiles());
    m_player->resolveEnemyCollisions(m_enemyManager->getEnemies());

    // give targets to the player? idk abotu this lol
    m_player->FindTarget(m_enemyManager->getEnemies());

    // update ui objects
    //ui_manager_->updateUiObjects(dt);

    debug_text_manager_->Update(*m_player);

    // remove unused objects
    m_enemyManager->removeUnusedEnemies();
    //ui_manager_->removeUnusedUiObjects();
}

void GameScene::render(SDL_Renderer* renderer)
{
    // render background hehhe
    const SDL_Rect background_rect = { 0, 0, m_windowWidth, m_windowHeight };
    SDL_RenderCopy(renderer, resource_manager_->GetTexture("background_forest_texture"), NULL, &background_rect);

    // render game objects
    m_enemyManager->RenderEnemies(renderer);
    m_player->Render(renderer);
    particle_manager_->RenderParticles(renderer);
    m_projectileManager->RenderProjectiles(renderer);

    // render ui objects
    //ui_manager_->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        m_enemyManager->RenderDebug(renderer);
        m_player->RenderDebug(renderer);
        m_projectileManager->renderDebug(renderer);
    }

    debug_text_manager_->Render(renderer);
}





