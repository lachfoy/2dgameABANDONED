#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class InputManager;
class ResourceManager;
class BaseUiObject;
class BaseActor;
class Player;

class UiManager
{
public:
    UiManager(std::shared_ptr<InputManager> inputManager, std::shared_ptr<ResourceManager> resourceManager, int windowWidth, int windowHeight);
    ~UiManager();

    std::vector<std::unique_ptr<BaseUiObject>> const& getUiObjects() const { return m_uiObjects; }
    
    void addHealthbar(int x, int y, int length, int height, BaseActor* damageable);
    void addDynamicHealthbar(int length, int height, BaseActor* damageable);
    void addCrosshair(int x, int y, int w, int h);
    void addTextObject(int x, int y, std::string text);
    void addPlayerDebugText(int x, int y, std::shared_ptr<Player> player);
    void addBackgroundFill(SDL_Color color);
    void addButton(int x, int y, std::string text);

    void updateUiObjects(float dt);
    void removeUnusedUiObjects();
    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<BaseUiObject>> m_uiObjects;
    int m_windowWidth;
    int m_windowHeight;

    // no ownership
    std::shared_ptr<InputManager> m_inputManager;
    std::shared_ptr<ResourceManager> m_resourceManager;

};

#endif