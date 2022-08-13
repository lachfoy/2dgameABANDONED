#include "GameScene.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "ParticleManager.h"

#define DEBUG_DRAW 0

GameScene::GameScene(InputManager* inputManager, ResourceManager* resourceManager, int windowWidth, int windowHeight)
     : BaseScene(inputManager, resourceManager, windowWidth, windowHeight)
{

}

void GameScene::create()
{
    m_resourceManager->loadGameTextures();

    m_uiManager = new UiManager(m_inputManager, m_resourceManager, m_windowWidth, m_windowHeight);
    m_particleManager = new ParticleManager(m_resourceManager);
    m_projectileManager = new ProjectileManager(m_resourceManager, m_particleManager);

    m_player = new Player(100.0f, 200.0f, m_resourceManager, m_uiManager, m_projectileManager);
    
    m_enemyManager = new EnemyManager(m_resourceManager, m_particleManager, m_uiManager, m_projectileManager, m_player);
    m_enemyManager->addSkeleton(400.0f, 300.0f);
    m_enemyManager->addSkeleton(600.0f, 400.0f);
    m_enemyManager->addSkeleton(500.0f, 500.0f);
    m_enemyManager->addSkeleton(300.0f, 400.0f);
    m_enemyManager->addSkeleton(700.0f, 200.0f);
}

void GameScene::destroy()
{
    delete m_enemyManager;
    delete m_player;
    delete m_projectileManager;
    delete m_particleManager;
    delete m_uiManager;
}

void GameScene::update(float dt)
{
    // handle input
    m_player->handleInput(*m_inputManager);

    // update game objects
    m_player->updatePlayer(dt);
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





