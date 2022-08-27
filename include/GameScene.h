#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "BaseScene.h"

class Player;
class ProjectileManager;
class EnemyManager;
class UiManager;
class ParticleManager;
class ParticleEmitterManager;
class DebugTextManager;

typedef std::shared_ptr<DebugTextManager> DebugTextManagerPtr;

class GameScene : public BaseScene
{
public:
    GameScene(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~GameScene();

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    DebugTextManagerPtr debug_text_manager_;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<ProjectileManager> m_projectileManager;
    std::shared_ptr<EnemyManager> m_enemyManager;
    std::shared_ptr<UiManager> ui_manager_;
    std::shared_ptr<ParticleManager> particle_manager_;
    std::shared_ptr<ParticleEmitterManager> particle_emitter_manager_;

};

#endif