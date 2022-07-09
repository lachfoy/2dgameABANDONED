#include "Game.h"

#include "Player.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "DamageCalculations.h"

Game::Game() {}

void Game::onCreate()
{
    Damage dmg = { .standard = 10, .crushing = 80 };
    Resistance rst = { .standard = 0, .crushing = 100 };
    DamageCalculations::damageAfterRestistance(dmg, rst);

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
    player->handleInput(*inputManager);

    // resolve projectile vs enemy collisions
    enemyManager->resolveProjectileCollisions(projectileManager->getProjectiles());

    // resolve enemy vs player collisions
    player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update the player
    player->update(dt);

    // update enemies
    enemyManager->updateEnemies(dt);

    // update projectiles
    projectileManager->updateProjectiles(dt);

    uiManager->updateUiObjects(dt);
}

void Game::onRender()
{
    // render game objects
    enemyManager->renderEnemies(renderer);
    player->render(renderer);
    projectileManager->renderProjectiles(renderer);

    // render UI objects
    uiManager->renderUiObjects(renderer);
}