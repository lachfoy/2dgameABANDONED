#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "BaseScene.h"

class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;
class ParticleManager;

class GameScene : public BaseScene
{
public:
    GameScene(InputManager* inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~GameScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    Player* m_player;
    ProjectileManager* m_projectileManager;
    EnemyManager* m_enemyManager;
    UiManager* m_uiManager;
    ParticleManager* m_particleManager;

};

#endif