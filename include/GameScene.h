#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "BaseScene.h"

class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;
class ParticleManager;

#include "ParticleEmitter.h"

class GameScene : public BaseScene
{
public:
    GameScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~GameScene();

    std::unique_ptr<ParticleEmitter> particle_emitter;

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<Player> m_player;
    std::shared_ptr<ProjectileManager> m_projectileManager;
    std::shared_ptr<EnemyManager> m_enemyManager;
    std::shared_ptr<UiManager> m_uiManager;
    std::shared_ptr<ParticleManager> m_particleManager;

};

#endif