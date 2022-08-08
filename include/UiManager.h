#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class InputManager;
class ResourceManager;
class BaseUiObject;
class BaseDamageable;
class Player;

class UiManager
{
public:
    UiManager(InputManager* inputManager, ResourceManager* resourceManager);
    ~UiManager();

    std::vector<BaseUiObject*> const& getUiObjects() const { return uiObjects; }
    
    void addHealthbar(int x, int y, int length, int height, BaseDamageable* damageable);
    void addDynamicHealthbar(int length, int height, BaseDamageable* damageable);
    void addCrosshair(int x, int y, int w, int h);
    void addTextObject(int x, int y, std::string text);
    void addPlayerDebugText(int x, int y, Player* player);

    void updateUiObjects(float dt);
    void removeUnusedUiObjects();
    void renderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<BaseUiObject*> uiObjects;
    TTF_Font* font;

    // no ownership
    InputManager* inputManager;
    ResourceManager* resourceManager;

};

#endif