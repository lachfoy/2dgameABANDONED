#include "Game.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"

Game::Game() {}

void Game::onCreate()
{
    uiManager = new UiManager();
    projectileManager = new ProjectileManager();

    player = new Player(100.0f, 200.0f, uiManager, projectileManager);
    
    enemyManager = new EnemyManager(player);
    enemyManager->addSkeleton(400.0f, 300.0f, uiManager, projectileManager);
    enemyManager->addSkeleton(600.0f, 400.0f, uiManager, projectileManager);
    enemyManager->addSkeleton(500.0f, 500.0f, uiManager, projectileManager);
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
    player->update(dt);
    enemyManager->updateEnemies(dt);
    projectileManager->updateProjectiles(dt);

    // collision resolution
    enemyManager->resolveProjectileCollisions(projectileManager->getProjectiles());
    player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update ui objects
    uiManager->updateUiObjects(dt);
}

void Game::onRender()
{
    // render game objects
    enemyManager->renderEnemies(renderer);
    player->render(renderer);
    projectileManager->renderProjectiles(renderer);

    // render ui objects
    uiManager->renderUiObjects(renderer);
}