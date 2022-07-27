#include "Game.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"

Game::Game() {}

void Game::onCreate()
{
    uiManager = new UiManager();
    projectileManager = new ProjectileManager(resourceManager);

    player = new Player(100.0f, 200.0f, resourceManager, uiManager, projectileManager);
    
    enemyManager = new EnemyManager(resourceManager, uiManager, projectileManager, player);
    enemyManager->addSkeleton(400.0f, 300.0f);
    enemyManager->addSkeleton(600.0f, 400.0f);
    enemyManager->addSkeleton(500.0f, 500.0f);
    enemyManager->addSkeleton(300.0f, 400.0f);
    enemyManager->addSkeleton(700.0f, 200.0f);
}

void Game::onCleanup()
{
    delete player;
    delete projectileManager;
    delete enemyManager;
    delete uiManager;
}

void Game::onUpdate(float dt)
{
    // handle input
    player->handleInput(*inputManager);

    // update game objects
    player->updatePlayer(dt);
    enemyManager->updateEnemies(dt);
    projectileManager->updateProjectiles(dt);

    // collision resolution
    enemyManager->resolvePlayerProjectileCollisions(projectileManager->getPlayerProjectiles());
    player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update ui objects
    uiManager->updateUiObjects(dt);

    // remove unused objects
    enemyManager->removeUnusedEnemies();
    projectileManager->removeUnusedProjectiles();
    uiManager->removeUnusedUiObjects();
}

void Game::onRender()
{
    // render game objects
    enemyManager->renderEnemies(renderer);
    player->renderShadow(renderer);
    player->render(renderer);
    projectileManager->renderProjectiles(renderer);

    // render ui objects
    uiManager->renderUiObjects(renderer);

    // debug
    if (DEBUG_DRAW)
    {
        enemyManager->renderDebug(renderer);
        player->renderDebug(renderer);
        projectileManager->renderDebug(renderer);
    }
}