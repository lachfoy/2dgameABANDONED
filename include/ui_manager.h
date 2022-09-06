#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include <vector>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class InputManager;
class ResourceManager;
class BaseUiObject;
class BaseCharacter;
class Player;

typedef std::shared_ptr<InputManager> InputManagerPtr;
typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;

class UiManager
{
public:
    UiManager(InputManagerPtr input_manager, ResourceManagerPtr resource_manager, int window_width, int window_height);
    ~UiManager();

    std::vector<std::unique_ptr<BaseUiObject>> const& getUiObjects() const { return ui_objects_; }
    
    void addHealthbar(int x, int y, int length, int height, BaseCharacter* damageable);
    void addDynamicHealthbar(int length, int height, BaseCharacter* damageable);
    void addTextObject(int x, int y, std::string text);

    void UpdateUiObjects(float dt);
    void CleanUpUnusedUiObjects();
    void RenderUiObjects(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<BaseUiObject>> ui_objects_;
    int window_width_;
    int window_height_;

    // no ownership
    InputManagerPtr input_manager_;
    ResourceManagerPtr resource_manager_;

};

#endif