#include "Skeleton.h"

#include "AABB2i.h"
#include "player.h"
#include "UiManager.h"
#include "EnemyManager.h"
#include "resource_manager.h"

Skeleton::Skeleton(const Vec2f& pos,
    std::shared_ptr<ResourceManager> resourceManager,
    std::shared_ptr<ParticleManager> particleManager,
    std::shared_ptr<UiManager> uiManager,
    std::shared_ptr<ProjectileManager> projectileManager,
    std::shared_ptr<Player> player)
     : BaseEnemy(pos, resourceManager, particleManager, uiManager, projectileManager, player)
{
    // initialize everything
    name_ = "Skeleton";
    
    width = 30;
    height = 50;

    colliderW = 40;
    colliderH = 30;

    maxHealth = 80;
    health = maxHealth;

    resistance = {0};
    resistance = { .crushingResistance = -80 };

    hurtCooldown = 0.1f; // how many seconds of iframes
    hurtTimer = hurtCooldown;

    startingMoveSpeed = 20.0f; // slowww
    moveSpeed = startingMoveSpeed;

    damage = {0};
    damage = { .crushing = 6 };

    thinkingTime = 2.0f;
    thinkingTimer = (float)((rand() % 2) + 1);
}

void Skeleton::updateAI(float dt)
{
    // do thinking. this is really messy :/
    thinkingTimer -= dt;
    if (thinkingTimer <= 0.0f)
    {
        printf("Skeleton had a thought...\n");
        target = player->pos();
        
        thinkingTimer = thinkingTime;  // reset to the starting value
    }

    dir = Vec2f::getDirection(pos_, target);
}

void Skeleton::render(SDL_Renderer* renderer)
{
    // create rect representing the enemy
    m_rect.x = (int)pos_.x - (width / 2);
    m_rect.y = (int)pos_.y - height;
    m_rect.w = width;
    m_rect.h = height;
    
    // set draw color
    m_color = { 0xff, 0xff, 0xff, 0xff }; // grey

    // set on fire ???
    if (isOnFire) m_color = { 0xff, 0x6a, 0x0d, 0xff }; // #ff6a0d more intense fire orange

    // owwwie
    if (isBeingHurt) m_color = { 0xff, 0x4e, 0x45, 0xff }; // #ff4e45

    // draw enemy
    // SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    // SDL_RenderFillRect(renderer, &m_rect);
    SDL_SetTextureColorMod(resource_manager_->GetTexture("skeleton_texture"), m_color.r, m_color.g, m_color.b);
    SDL_RenderCopy(renderer, resource_manager_->GetTexture("skeleton_texture"), NULL, &m_rect);
}
