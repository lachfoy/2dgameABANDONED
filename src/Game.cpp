#include "Game.h"

#include "AABB.h"
#include "Player.h"
#include "HealthBar.h"
#include "ProjectileManager.h"
#include "UIManager.h"

Game::Game() {}

void Game::onCreate()
{
    _UIManager = new UIManager();
    player = new Player(100.0f, 200.0f);
    projectileManager = new ProjectileManager();
    //enemyManager = new EnemyManager();
    test_collider = new AABB(300.0f, 200.0f, 200.0f, 100.0f);
    //enemyManager->addSkeleton(player, *_UIManager, 400.0f, 300.0f);
}

void Game::onCleanup()
{
    delete player;
    delete projectileManager;
    //delete enemyManager;
    delete _UIManager;
}

void Game::onUpdate(float dt)
{
    player->handleInput(*inputManager);

    // resolve projectile vs enemy collisions
    //enemyManager->resolveProjectileCollisions(projectileManager->getProjectiles());

    // resolve enemy vs player collisions
    //player->resolveEnemyCollisions(enemyManager->getEnemies());

    // update the player
    player->onUpdate(*projectileManager, dt);

    // update enemies
    //enemyManager->updateEnemies(dt);

    // update projectiles
    projectileManager->updateProjectiles(dt);
}

void Game::onRender()
{
    // render game objects
    //enemyManager->renderEnemies(renderer);
    player->render(renderer);
    projectileManager->renderProjectiles(renderer);

    // render UI objects
    _UIManager->renderUIObjects(renderer);
}